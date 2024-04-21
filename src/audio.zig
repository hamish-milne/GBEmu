const std = @import("std");
const C = @import("C.zig");

fn RingBuffer(comptime T: type, comptime stride: usize, comptime len: usize) type {
    return struct {
        Data: [len * stride]T = undefined,
        Read: usize = 0,
        Write: usize = 0,
        Count: isize = 0,

        fn write(buffer: *@This(), value: [stride]T) void {
            const idx = @atomicLoad(usize, &buffer.Write, .Monotonic);
            inline for (0..stride) |i| {
                @atomicStore(T, &buffer.Data[idx * stride + i], value[i], .Unordered);
            }
            @atomicStore(usize, &buffer.Write, (idx + 1) % len, .Monotonic);
            @fence(.AcqRel);
            _ = @atomicRmw(isize, &buffer.Count, .Add, 1, .Monotonic);
            _ = @atomicRmw(isize, &buffer.Count, .Max, len, .Monotonic);
        }

        fn read(buffer: *@This(), value: *[stride]T) bool {
            if (@atomicRmw(isize, &buffer.Count, .Sub, 1, .Monotonic) <= 0) {
                _ = @atomicRmw(isize, &buffer.Count, .Add, 1, .Monotonic);
                return false;
            }
            @fence(.AcqRel);
            const idx = @atomicLoad(usize, &buffer.Read, .Monotonic);
            inline for (0..stride) |i| {
                value[i] = @atomicLoad(T, &buffer.Data[idx * stride + i], .Unordered);
            }
            @atomicStore(usize, &buffer.Read, (idx + 1) % len, .Monotonic);
            return true;
        }

        fn count(buffer: *@This()) isize {
            return @atomicLoad(isize, &buffer.Count, .Monotonic);
        }
    };
}

const SampleRate = 48000;
pub const AudioRingBuffer = RingBuffer(f32, 2, SampleRate / 50);

fn soundioCall(err: c_int) !void {
    if (err != 0) {
        std.debug.print("{s}\n", .{C.soundio_strerror(err)});
        return error.AudioError;
    }
}

pub const State = struct {
    SoundIO: *C.SoundIo,
    Device: *C.SoundIoDevice,
    OutStream: *C.SoundIoOutStream,

    pub fn init(self: *State, buffer: *AudioRingBuffer) !void {
        self.SoundIO = C.soundio_create() orelse return error.AudioError;
        try soundioCall(C.soundio_connect(self.SoundIO));
        C.soundio_flush_events(self.SoundIO);
        const deviceIdx = C.soundio_default_output_device_index(self.SoundIO);
        if (deviceIdx < 0) {
            return error.NoAudioDevice;
        }
        self.Device = C.soundio_get_output_device(self.SoundIO, deviceIdx) orelse return error.AudioError;
        self.OutStream = C.soundio_outstream_create(self.Device) orelse return error.AudioError;
        self.OutStream.userdata = @ptrCast(buffer);
        self.OutStream.format = C.SoundIoFormatFloat32NE;
        self.OutStream.format = SampleRate;
        self.OutStream.layout = C.soundio_channel_layout_get_builtin(C.SoundIoChannelLayoutIdStereo).*;
        self.OutStream.write_callback = writeCallback;
        try soundioCall(C.soundio_outstream_open(self.OutStream));
        try soundioCall(C.soundio_outstream_start(self.OutStream));
    }

    pub fn deinit(self: *State) void {
        C.soundio_outstream_destroy(self.OutStream);
        C.soundio_device_unref(self.Device);
        C.soundio_destroy(self.SoundIO);
    }
};

fn writeCallback(outStream: [*c]C.SoundIoOutStream, frameCountMin: c_int, frameCountMax: c_int) callconv(.C) void {
    const buffer: *AudioRingBuffer = @alignCast(@ptrCast(outStream.*.userdata));
    _ = frameCountMin;
    const layout = outStream.*.layout;

    const available: c_int = @intCast(buffer.count());
    var framesLeft = @max(frameCountMax, available);
    while (framesLeft > 0) {
        var frameCount = framesLeft;
        var areas: [*c]C.SoundIoChannelArea = undefined;
        soundioCall(C.soundio_outstream_begin_write(outStream, &areas, &frameCount)) catch return;

        if (frameCount == 0) {
            break;
        }

        for (0..@intCast(frameCount)) |frame| {
            var value: [2]f32 = undefined;
            if (!buffer.read(&value)) {
                break;
            }
            for (0..@intCast(@min(layout.channel_count, 2))) |channel| {
                const step: usize = @intCast(areas[channel].step);
                const area = areas[channel].ptr + (step * frame);
                const ptr: *f32 = @alignCast(@ptrCast(area));
                ptr.* = value[channel];
            }
        }

        soundioCall(C.soundio_outstream_end_write(outStream)) catch return;

        framesLeft -= frameCount;
    }
}

const Audio = struct {
    DIVAPU: u8,

    C1Length: u6,
    C1Sweep: u8,
    C1Period: u11,
    C1Sample: u3,
    C1Volume: u4,
    C1VolumeSweep: u3,

    C2Length: u6,
    C2Period: u11,
    C2Sample: u3,
    C2Volume: u4,
    C2VolumeSweep: u3,

    C3Length: u8,
    C3Period: u11,
    C3Sample: u3,

    LFSR: u16,
    C4Length: u6,
    C4Volume: u4,
    C4VolumeSweep: u3,

    Outputs: [4]u4,
    SampleBuffer: [437][2]u16,
    SampleBufferIdx: usize,

    fn audio(self: *Audio) void {
        const NR52 = &self.IOPorts.NR52;
        if (!NR52.SoundEnable) {
            return;
        }

        const div2 = self.DIVAPU & 0b1 == 0;
        const div4 = self.DIVAPU & 0b11 == 0;
        const div8 = self.DIVAPU & 0b1111 == 0;

        const doPulse = self.Time.Current % 4 == 0;
        const doWave = self.Time.Current % 2 == 0;

        const pulseWaveforms: [4]u8 = .{
            0b01111111,
            0b00111111,
            0b00001111,
            0b00000011,
        };

        if (NR52.C1Active and doPulse) {
            const NR10 = &self.IOPorts.NR10;
            const Sound1 = &self.IOPorts.Sound1;

            if (Sound1.LengthEnable and div2) {
                if (self.C1Length >= 63) {
                    NR52.C1Active = false;
                    self.Outputs[0] = 0;
                } else {
                    self.C1Length += 1;
                }
            }

            if (NR10.SweepPace > 0 and div4) {
                if (self.C1Sweep <= 1) {
                    self.C1Sweep = NR10.SweepPace;
                    const period: u16 = Sound1.Period;
                    const newPeriod = if (NR10.SweepDirection)
                        period +% (period >> NR10.SweepShift)
                    else
                        period -% (period >> NR10.SweepShift);
                    if (newPeriod < 2048) {
                        Sound1.Period = @intCast(newPeriod);
                    } else {
                        NR52.C1Active = false;
                    }
                } else {
                    self.C1Sweep -= 1;
                }
            }

            if (Sound1.EnvelopeSweep > 0 and div8) {
                self.C1VolumeSweep +%= 1;
                if (self.C1VolumeSweep >= Sound1.EnvelopeSweep) {
                    self.C1VolumeSweep = 0;
                    switch (Sound1.EnvelopeDirection) {
                        1 => if (Sound1.Volume < 15) {
                            Sound1.Volume += 1;
                        },
                        0 => if (Sound1.Volume > 0) {
                            Sound1.Volume -= 1;
                        },
                    }
                }
            }

            self.C1Period +%= 1;
            if (self.C1Period == 0) {
                self.C1Period = Sound1.Period;
                self.C1Sample +%= 1;
            }

            const waveform = pulseWaveforms[Sound1.WaveDuty];
            self.Outputs[0] = if (waveform >> self.C1Sample != 0) Sound1.Volume else 0;
        }

        if (doPulse and NR52.C2Active) {
            const Sound2 = &self.IOPorts.Sound2;

            if (Sound2.LengthEnable and div2) {
                if (self.C2Length >= 63) {
                    NR52.C2Active = false;
                    self.Outputs[1] = 0;
                } else {
                    self.C2Length += 1;
                }
            }

            if (Sound2.EnvelopeSweep > 0 and div8) {
                self.C2VolumeSweep +%= 1;
                if (self.C2VolumeSweep >= Sound2.EnvelopeSweep) {
                    self.C2VolumeSweep = 0;
                    switch (Sound2.EnvelopeDirection) {
                        1 => if (Sound2.Volume < 15) {
                            Sound2.Volume += 1;
                        },
                        0 => if (Sound2.Volume > 0) {
                            Sound2.Volume -= 1;
                        },
                    }
                }
            }

            self.C2Period +%= 1;
            if (self.C2Period == 0) {
                self.C2Period = Sound2.Period;
                self.C2Sample +%= 1;
            }

            const waveform = pulseWaveforms[Sound2.WaveDuty];
            self.Outputs[1] = if (waveform >> self.C1Sample != 0) Sound2.Volume else 0;
        }

        if (doWave and NR52.C3Active and self.IOPorts.NR30.Enable) {
            const Sound3 = &self.IOPorts.Sound3;

            if (Sound3.LengthEnable and div2) {
                if (self.C3Length >= 255) {
                    NR52.C3Active = false;
                    self.Outputs[2] = 0;
                } else {
                    self.C3Length += 1;
                }
            }

            self.C3Period +%= 1;
            if (self.C3Period == 0) {
                self.C3Period = Sound3.Period;
                self.C3Sample +%= 1;
            }

            const shift = if (Sound3.Volume == 0) 4 else (Sound3.Volume - 1);
            self.Outputs[2] = self.IOPorts.WavePattern.get(self.C3Sample ^ 0b1) >> shift;
        }

        if (NR52.C4Active) {
            const Sound4 = &self.IOPorts.Sound4;

            if (Sound4.LengthEnable and div2) {
                if (self.C4Length >= 63) {
                    NR52.C4Active = false;
                    self.Outputs[3] = 0;
                } else {
                    self.C4Length += 1;
                }
            }

            if (Sound4.EnvelopeSweep > 0 and div8) {
                self.C4VolumeSweep +%= 1;
                if (self.C4VolumeSweep >= Sound4.EnvelopeSweep) {
                    self.C4VolumeSweep = 0;
                    switch (Sound4.EnvelopeDirection) {
                        1 => if (Sound4.Volume < 15) {
                            Sound4.Volume += 1;
                        },
                        0 => if (Sound4.Volume > 0) {
                            Sound4.Volume -= 1;
                        },
                    }
                }
            }

            self.C4Period +%= 1;
            if (self.C4Period == 0) {
                self.C4Period = Sound4.Freq;
                self.C4Sample +%= 1;
            }
        }

        const NR50 = &self.IOPorts.NR50;
        const NR51 = &self.IOPorts.NR51;
        var s0: u16 = 0;
        var s1: u16 = 0;
        inline for (0..4) |i| {
            s0 += if ((NR51.S01Channels & (1 << i)) != 0) self.Outputs[i] * (NR50.S01Volume + 1) else 0;
            s1 += if ((NR51.S02Channels & (1 << i)) != 0) self.Outputs[i] * (NR50.S01Volume + 1) else 0;
        }

        self.SampleBuffer[self.SampleBufferIdx] = .{ s0, s1 };
        self.SampleBufferIdx += 1;

        if (self.SampleBufferIdx >= self.SampleBuffer.len) {
            self.SampleBufferIdx = 0;
            // channel output * max volume * number of channels * buffer size
            const MaxValue = 0xF * 8 * 4 * self.SampleBuffer.len;
            var avg: @Vector(2, u32) = .{ 0, 0 };
            for (0..self.SampleBuffer.len) |i| {
                avg += self.SampleBuffer[i];
            }
            AudioRingBuffer.write(.{ avg[0] / MaxValue, avg[1] / MaxValue });
        }
    }
};
