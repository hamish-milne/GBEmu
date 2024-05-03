const std = @import("std");
const C = @import("C.zig");
const audio = @import("audio.zig");
const memory = @import("memory.zig");
const cpu = @import("cpu.zig");
const graphics = @import("graphics.zig");

const BootROM = @embedFile("DMG_ROM.bin");

pub const GameState = struct {
    Memory: memory.Memory,
    CPU: cpu.CPU,
    Screen: graphics.Screen,
    Audio: audio.Audio,
    AudioBuffer: *audio.AudioRingBuffer,

    Time: struct {
        Current: u64 = 0,
        NextInstruction: u64 = 0,
        LCD: u64 = 0,
    },

    fn advanceWithAudio(self: *GameState, until: u64) void {
        while (self.Time.Current < until) {
            self.Audio.main(self.Time.Current, &self.Memory.IOPorts, self.AudioBuffer);
            self.Time.Current += audio.AudioClockStep;
        }
    }

    pub fn init(self: *GameState, audioBuffer: *audio.AudioRingBuffer, rom: []const u8) void {
        @memset(memory.asBytes(GameState, self), 0);
        self.Memory.BootROM = BootROM;
        self.Memory.ROM = rom;
        self.Memory.setMBC();
        self.CPU.mem = &self.Memory;
        self.AudioBuffer = audioBuffer;
        self.Time = .{};
    }

    pub fn mainLoop(self: *GameState) void {
        self.CPU.mem = &self.Memory;
        const IOPorts = &self.Memory.IOPorts;
        while (true) {
            if (self.CPU.interrupt()) {
                self.advanceWithAudio(self.Time.Current + 20);
            }
            while (self.CPU.RunState == .Running and self.Time.NextInstruction < self.Time.LCD) {
                self.advanceWithAudio(self.Time.NextInstruction);
                self.Time.NextInstruction = self.Time.Current + self.CPU.opMain() * 4;
            }
            self.advanceWithAudio(self.Time.LCD);
            if (IOPorts.LCDC.LCDEnable) {
                switch (IOPorts.STAT.Mode) {
                    .HBlank => {
                        IOPorts.LY += 1;
                        if (IOPorts.LY >= 144) {
                            IOPorts.IF.VBlank = true;
                            IOPorts.STAT.Mode = .VBlank;
                            if (IOPorts.STAT.InterruptEnable.VBlank)
                                IOPorts.IF.LCDC = true;
                            self.Time.LCD += 456;
                            return;
                        } else {
                            IOPorts.STAT.Mode = .OAMRead;
                            if (IOPorts.STAT.InterruptEnable.OAMRead)
                                IOPorts.IF.LCDC = true;
                            self.Time.LCD += 80;
                        }
                    },
                    .VBlank => {
                        if (IOPorts.LY >= 153) {
                            IOPorts.LY = 0;
                            IOPorts.STAT.Mode = .OAMRead;
                            if (IOPorts.STAT.InterruptEnable.OAMRead)
                                IOPorts.IF.LCDC = true;
                            self.Time.LCD += 80;
                        } else {
                            IOPorts.LY += 1;
                            self.Time.LCD += 456;
                        }
                    },
                    .OAMRead => {
                        IOPorts.STAT.Mode = .Transfer;
                        self.Time.LCD += 172;
                    },
                    .Transfer => {
                        graphics.drawLine(&self.Memory, &self.Screen);
                        IOPorts.STAT.Mode = .HBlank;
                        if (IOPorts.STAT.InterruptEnable.HBlank)
                            IOPorts.IF.LCDC = true;
                        self.Time.LCD += 204;
                    },
                }
            } else {
                IOPorts.STAT.Mode = .VBlank;
                self.Time.LCD += 70224;
                return;
            }
            if (IOPorts.LY == IOPorts.LYC and IOPorts.STAT.InterruptEnable.LYCCoincidence) {
                IOPorts.IF.LCDC = true;
            }
        }
    }
};
