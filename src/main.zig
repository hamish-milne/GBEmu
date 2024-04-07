const std = @import("std");
const C = @cImport({
    @cInclude("GLFW/glfw3.h");
    @cInclude("soundio/soundio.h");
});

const InterruptFlags = packed struct {
    VBlank: bool,
    LCDC: bool,
    Timer: bool,
    SerialIO: bool,
    Button: bool,
    _: u3,
};

const TileDataFlag = enum(u1) {
    x88,
    x80,
};

const Palette = std.PackedIntArray(u2, 4);

fn asBytes(comptime T: type, value: *T) *[@sizeOf(T)]u8 {
    return @as([*]u8, @ptrCast(value))[0..@sizeOf(T)];
}

const IOPorts = struct {
    // zig fmt: off
    P1: packed struct {
        P10: bool,
        P11: bool,
        P12: bool,
        P13: bool,
        P14: bool,
        P15: bool,
        _: u2
    } align(1),
    // zig fmt: on
    SB: u8 align(1),
    SC: packed struct {
        ShiftClock: bool,
        _: u6,
        TransferStart: bool,
    } align(1),
    _: u8 align(1),
    DIV: u8 align(1),
    TIMA: u8 align(1),
    TMA: u8 align(1),
    TAC: packed struct {
        ClockSelect: u2,
        TimerStart: bool,
        _: u5,
    } align(1),
    _1: [7]u8 align(1),
    IF: InterruptFlags align(1),
    NR10: packed struct {
        SweepStep: u3,
        SweepDir: bool,
        SweepPace: u3,
        _: u1,
    } align(1),
    Sound1: packed struct {
        // NR11
        SoundLength: u6,
        WaveDuty: u2,
        // NR12
        EnvelopeSweep: u3,
        EnvelopeDirection: u1,
        EnvelopeInitial: u4,
        // NR13..14
        Period: u11,
        _1: u3,
        LengthEnable: bool,
        Initial: bool,
    } align(1),
    _2: u8 align(1),
    Sound2: packed struct {
        // NR21
        SoundLength: u6,
        WaveDuty: u2,
        // NR22
        EnvelopeSweep: u3,
        EnvelopeDirection: u1,
        EnvelopeInitial: u4,
        // NR23..24
        Period: u11,
        _: u3,
        LengthEnable: bool,
        Initial: bool,
    } align(1),
    NR30: packed struct {
        _: u7,
        Enable: bool,
    } align(1),
    Sound3: packed struct {
        // NR31
        Length: u8,
        // NR32
        _1: u5,
        OutputLevel: enum(u2) { Mute, Full, Half, Quarter },
        _2: u1,
        // NR33..34
        Frequency: u11,
        _3: u3,
        LengthEnable: bool,
        Initial: bool,
    } align(1),
    _3: u8,
    Sound4: packed struct {
        // NR41
        SoundLength: u6,
        _: u2,
        // NR42
        EnvelopeSweep: u3,
        EnvelopeDirection: u1,
        EnvelopeInitial: u4,
        // NR43
        FreqDiv: u3,
        Step: u1,
        Freq: u4,
        // NR44
        _1: u5,
        CounterMode: u1,
        Initial: bool,
    } align(1),
    NR50: packed struct {
        S01Volume: u3,
        S01Vin: bool,
        S02Volume: u3,
        S02Vin: bool,
    } align(1),
    NR51: packed struct {
        S01Channels: u4,
        S02Channels: u4,
    } align(1),
    // zig fmt: off
    NR52: packed struct {
        C1Active: bool,
        C2Active: bool,
        C3Active: bool,
        C4Active: bool,
        _: u3,
        SoundEnable: bool,
    } align(1),
    _4: [9]u8,
    WavePattern: std.PackedIntArray(u4, 32) align(1),
    LCDC: packed struct {
        BGEnable: bool,
        SpriteEnable: bool,
        SpriteSize: enum(u1) {
            S8x8,
            S8x16,
        },
        BGTileMap: u1,
        BGWindowTileData: TileDataFlag,
        WindowEnable: bool,
        WindowTileMap: u1,
        LCDEnable: bool
    } align(1),
    // zig fmt: on
    STAT: packed struct {
        Mode: enum(u2) {
            HBlank,
            VBlank,
            OAMRead,
            Transfer,
        },
        LYCCoincidence: bool,
        InterruptEnable: packed struct {
            HBlank: bool,
            VBlank: bool,
            OAMRead: bool,
            LYCCoincidence: bool,
        },
        _: u1,
    } align(1),
    SCY: u8 align(1),
    SCX: u8 align(1),
    LY: u8 align(1),
    LYC: u8 align(1),
    DMA: u8 align(1),
    BGP: Palette align(1),
    OBP0: Palette align(1),
    OBP1: Palette align(1),
    WY: u8 align(1),
    WX: u8 align(1),
    _5: u32 align(1),
    BOOT: packed struct {
        BOOT: bool,
        _: u7,
    } align(1),
};

const WriteMask: IOPorts = .{
    .P1 = 0b00110000,
    .SB = 0b11111111,
    .SC = 0b10000001,
    ._ = 0,
    .DIV = 0,
    .TIMA = 0b11111111,
    .TMA = 0b11111111,
    .TAC = 0b00000111,
    ._1 = .{ 0, 0, 0, 0, 0, 0, 0 },
    .IF = .{
        .VBlank = true,
        .LCDC = true,
        .Timer = true,
        .SerialIO = true,
        .Button = true,
        ._ = 0,
    },
};

fn specialRegs(offset: u8) void {
    switch (offset) {
        @offsetOf(IOPorts, "DIV") => {
            // DIV
            // self.IOPorts.DIV = 0;
        },
    }
}

const VRAM = struct {
    Data: [0x180][8]u16,
    Map: [2][0x20][0x20]u8,
};

const OAM = [40](packed struct { Y: u8, X: u8, Tile: u8, Flags: packed struct {
    _: u4,
    Palette: enum(u1) { OBJ0PAL, OBJ1PAL },
    XFlip: bool,
    YFlip: bool,
    Priority: u1,
} });

comptime {
    if (@sizeOf(IOPorts) != 0x51) {
        unreachable;
    }
    if (@sizeOf(VRAM) != 0x2000) {
        unreachable;
    }
    if (@sizeOf(OAM) != 0xA0) {
        unreachable;
    }
}

// zig fmt: off
const GameState = struct {
    Time: struct {
        Current: u64 = 0,
        NextInstruction: u64 = 0,
        LCD: u64 = 0,
    },
    RunState: enum {
        Running,
        HALT,
        STOP,
    } = .Running,
    Error: enum {
        None,
        InvalidOpcode,
    } = .None,
    IOPorts: IOPorts,
    SP: u16,
    PC: u16,
    R: packed union {
        u8: packed struct {
            F: packed struct {
                _: u4,
                C: bool,
                H: bool,
                N: bool,
                Z: bool,
            },
            A: u8,
            C: u8,
            B: u8,
            E: u8,
            D: u8,
            L: u8,
            H: u8,
        },
        u16: packed struct {
            AF: u16,
            BC: u16,
            DE: u16,
            HL: u16,
        },
    },
    HiRAM: [0x80]u8,
    OAM: OAM,
    IntRAM: [0x2000]u8,
    VRAM: VRAM,
    MBC: union(enum) {
        ROMOnly: void,
        MBC1: struct {
            ROMBank: u5,
            RAMBank: union(enum) { RAMBankSel: u2, ROMBankSel: u2 },
            RAMEnable: bool,
            Data: [4][0x2000]u8,
        },
        MBC2: struct {
            ROMBank: u4,
            RAMEnable: bool,
            Data: [0x100]u8,
        },
        MBC3: struct {
            ROMBank: u7,
            RAMBank: u2,
            RAMEnable: bool,
            Data: [4][0x2000]u8,
        },
        MBC5: struct {
            ROMBank: u9,
            RAMBank: u4,
            RAMEnable: bool,
            Data: [16][0x2000]u8,
        }
    },
    IME: bool,
    Audio: struct {
        DIVAPU: u8,
        DIVAPUPrev: u8,
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
    },
    ROM: []const u8,
    Screen: [144][160]u8,

    fn read(self: *GameState, addr: u16) u8 {
        const topNibble: u4 = @intCast((addr & 0xF000) >> 12);
        return switch (topNibble) {
            0x0 ... 0x3 => if (addr >= self.ROM.len) 0 else self.ROM[addr],
            0x4 ... 0x7 => blk: {
                const romBank = switch (self.MBC) {
                    .ROMOnly => 0,
                    .MBC1 => |mbc1| mbc1.ROMBank | switch (mbc1.RAMBank) {
                        .ROMBankSel => |upper| @as(u8, upper) << 5,
                        else => 0
                    },
                    .MBC2 => |mbc2| mbc2.ROMBank,
                    .MBC3 => |mbc3| mbc3.ROMBank,
                    .MBC5 => |mbc5| mbc5.ROMBank,
                };
                const fullAddr = (@as(u32, romBank) << 14) | addr;
                break :blk if (fullAddr >= self.ROM.len) 0 else self.ROM[fullAddr];
            },
            0x8 ... 0x9 => asBytes(VRAM, &self.VRAM)[addr & 0x1FFF],
            0xA ... 0xB => switch (self.MBC) {
                .ROMOnly => 0,
                .MBC1 => |mbc1| if (mbc1.RAMEnable) switch (mbc1.RAMBank) {
                    .RAMBankSel => |ramBank| mbc1.Data[ramBank][addr & 0x1FFF],
                    else => 0,
                } else 0,
                .MBC2 => |mbc2| if (mbc2.RAMEnable) mbc2.Data[addr & 0xFF] else 0,
                .MBC3 => |mbc3| if (mbc3.RAMEnable) mbc3.Data[mbc3.RAMBank][addr & 0x1FFF] else 0,
                .MBC5 => |mbc5| if (mbc5.RAMEnable) mbc5.Data[mbc5.RAMBank][addr & 0x1FFF] else 0,
            },
            0xC ... 0xE => self.IntRAM[addr & 0x1FFF],
            0xF => switch ((addr & 0x0F00) >> 8) {
                0xE => blk: {
                    const oamBytes = asBytes(OAM, &self.OAM);
                    const localAddr = addr & 0xFF;
                    break :blk if (localAddr < oamBytes.len) oamBytes[localAddr] else 0;
                },
                0xF => if (addr < 0xFF80) blk: {
                    const ioportsBytes = asBytes(IOPorts, &self.IOPorts);
                    const localAddr = addr & 0xFF;
                    break :blk if (localAddr < ioportsBytes.len) ioportsBytes[localAddr] else 0;
                } else self.HiRAM[addr & 0x7f],
                else => self.IntRAM[addr & 0x1FFF]
            }
        };
    }

    fn write(self: *GameState, addr: u16, value: u8) void {
        const topNibble: u4 = @intCast((addr & 0xF000) >> 12);
        switch (topNibble) {
            0x0 ... 0x1 => {
                const enable = (value & 0b1111) == 0b1010;
                switch (self.MBC) {
                    .MBC1 => |*mbc1| mbc1.RAMEnable = enable,
                    .MBC2 => |*mbc2| if (addr & 0x0100 != 0) { mbc2.RAMEnable = enable; },
                    .MBC3 => |*mbc3| mbc3.RAMEnable = enable,
                    .MBC5 => |*mbc5| mbc5.RAMEnable = enable,
                    else => {},
                }
            },
            0x2 ... 0x3 => {
                switch (self.MBC) {
                    .MBC1 => |*mbc1| mbc1.ROMBank = @truncate(value),
                    .MBC2 => |*mbc2| if (addr & 0x0100 == 0) { mbc2.ROMBank = @truncate(value); },
                    .MBC3 => |*mbc3| mbc3.ROMBank = @truncate(value),
                    .MBC5 => |*mbc5| if (addr < 0x3000) {
                        mbc5.ROMBank = (mbc5.ROMBank & 0b011111111) | (@as(u9, value & 0b1) << 8);
                    } else {
                        mbc5.ROMBank = (mbc5.ROMBank & 0b100000000) | value;
                    },
                    else => {},
                }
            },
            0x4 ... 0x5 => {
                switch (self.MBC) {
                    .MBC1 => |*mbc1| switch (mbc1.RAMBank) {
                        .RAMBankSel => |*ptr| ptr.* = @truncate(value),
                        .ROMBankSel => |*ptr| ptr.* = @truncate(value)
                    },
                    else => {},
                }
            },
            0x6 ... 0x7 => {},
            0x8 ... 0x9 => asBytes(VRAM, &self.VRAM)[addr & 0x1FFF] = value,
            0xA ... 0xB => switch (self.MBC) {
                .MBC1 => |*mbc1| if (mbc1.RAMEnable) switch (mbc1.RAMBank) {
                    .RAMBankSel => |ramBank| mbc1.Data[ramBank][addr & 0x1FFF] = value,
                    else => {},
                },
                .MBC2 => |*mbc2| if (mbc2.RAMEnable) { mbc2.Data[addr & 0xFF] = value; },
                .MBC3 => |*mbc3| if (mbc3.RAMEnable) { mbc3.Data[mbc3.RAMBank][addr & 0x1FFF] = value; },
                .MBC5 => |*mbc5| if (mbc5.RAMEnable) { mbc5.Data[mbc5.RAMBank][addr & 0x1FFF] = value; },
                else => {},
            },
            0xC ... 0xE => self.IntRAM[addr & 0x1FFF] = value,
            0xF => switch ((addr & 0x0F00) >> 8) {
                0xE => {
                    const oamBytes = asBytes(OAM, &self.OAM);
                    const localAddr = addr & 0xFF;
                    if (localAddr < oamBytes.len) oamBytes[localAddr] = value;
                },
                0xF => if (addr < 0xFF80) {
                    const ioportsBytes = asBytes(IOPorts, &self.IOPorts);
                    const localAddr = addr & 0xFF;
                    if (localAddr < ioportsBytes.len) { ioportsBytes[localAddr] = value; }
                } else { self.HiRAM[addr & 0x7f] = value; },
                else => self.IntRAM[addr & 0x1FFF] = value
            }
        }
    }

    fn readU16(self: *GameState, addr: u16) u16 {
        return (@as(u16, self.read(addr + 1)) << 8) | self.read(addr);
    }

    fn writeU16(self: *GameState, addr: u16, value: u16) void {
        self.write(addr, @truncate(value));
        self.write(addr + 1, @truncate(value >> 8));
    }

    fn add(self: *GameState, a: u8, b: u8, c: u1, setC: bool) u8 {
        const result = @as(u16, a) + @as(u16, b) + @as(u16, c);
        const value: u8 = @truncate(result);
        self.R.u8.F.Z = value == 0;
        self.R.u8.F.N = false;
        self.R.u8.F.H = (a & 0xF) + (b & 0xF) > 0xF;
        if (setC) {
            self.R.u8.F.C = result > 0xFF;
        }
        return value;
    }

    fn add16(self: *GameState, a: u16, b: u16, setFlags: bool) u16 {
        const result = @as(u32, a) + @as(u32, b);
        const value: u16 = @truncate(result);
        if (setFlags) {
            self.R.u8.F.Z = value == 0;
            self.R.u8.F.N = false;
            self.R.u8.F.H = (a & 0xFFF) + (b & 0xFFF) > 0xFFF;
            self.R.u8.F.C = result > 0xFF;
        }
        return value;
    }

    fn flags(self: *GameState, value: u8, h: bool, c: bool) u8 {
        self.R.u8.F.Z = value == 0;
        self.R.u8.F.N = false;
        self.R.u8.F.H = h;
        self.R.u8.F.C = c;
        return value;
    }

    fn readReg(self: *GameState, selector: u3) u8 {
        return switch (selector) {
            0 => self.R.u8.B,
            1 => self.R.u8.C,
            2 => self.R.u8.D,
            3 => self.R.u8.E,
            4 => self.R.u8.H,
            5 => self.R.u8.L,
            6 => self.read(self.R.u16.HL),
            7 => self.R.u8.A,
        };
    }

    fn writeReg(self: *GameState, selector: u3, value: u8) void {
        switch (selector) {
            0 => self.R.u8.B = value,
            1 => self.R.u8.C = value,
            2 => self.R.u8.D = value,
            3 => self.R.u8.E = value,
            4 => self.R.u8.H = value,
            5 => self.R.u8.L = value,
            6 => self.write(self.R.u16.HL, value),
            7 => self.R.u8.A = value,
        }
    }

    fn regCost(reg: u3) u8 {
        return switch (reg) {
            6 => 2,
            else => 1,
        };
    }

    fn readPC(self: *GameState) u8 {
        const pc = self.PC;
        self.PC += 1;
        return self.read(pc);
    }

    
    fn jumpRel(self: *GameState) void {
        const offset: i8 = @bitCast(self.readPC());
        self.PC +%= @bitCast(@as(i16, offset));
    }

    fn readPC16(self: *GameState) u16 {
        const low = self.readPC();
        const high: u16 = self.readPC();
        return (high << 8) | low;
    }

    fn regPtr16(self: *GameState, inst: u8) *u16 {
        const selector: u2 = @intCast((inst & 0b110000) >> 4);
        return switch (selector) {
            0 => &self.R.u16.BC,
            1 => &self.R.u16.DE,
            2 => &self.R.u16.HL,
            3 => &self.SP,
        };
    }

    fn push(self: *GameState, value: u16) void {
        self.SP -%= 2;
        self.writeU16(self.SP, value);
    }

    fn pop(self: *GameState) u16 {
        const value = self.readU16(self.SP);
        self.SP +%= 2;
        return value;
    }

    fn rotate(self: *GameState, variant: u2, value: u8) u8 {
        const newC = switch (variant) {
            // RL, RLC
            0, 2 => value >> 7,
            // RR, RRC
            1, 3 => value & 1,
        };
        const newBit: u8 = switch (variant) {
            // RLC, RRC
            0, 1 => newC,
            // RL, RR
            2, 3 => if (self.R.u8.F.C) 1 else 0,
        };
        const newValue = switch (variant) {
            // RL, RLC
            0, 2 => (value << 1) | newBit,
            // RR, RRC
            1, 3 => (value >> 1) | (newBit << 7),
        };
        return self.flags(newValue, false, newC != 0);
    }

    fn cond(self: *GameState, inst: u8) bool {
        const selector: u2 = @intCast((inst & 0b00011000) >> 3);
        return switch (selector) {
            0 => !self.R.u8.F.Z,
            1 => !self.R.u8.F.C,
            2 => self.R.u8.F.Z,
            3 => self.R.u8.F.C
        };
    }

    fn opMain(self: *GameState) u8 {
        const inst = self.readPC();
        const block2: u3 = @intCast((inst & 0b00111000) >> 3);
        const block1: u3 = @intCast(inst & 0b111);
        const bit7 = (inst & 0b10000000) != 0;
        const bit6 = (inst & 0b1000000) != 0;
        const bit4 = (inst & 0b10000) != 0;
        const bit3 = (inst & 0b1000) != 0;
        const bit0 = (inst & 0b1) != 0;
        const isImmediate = (inst & 0b111) == 0b110;

        if (inst == 0x76) {
            // HALT
            self.RunState = .HALT;
            return 0;
        }

        if (!bit7) {
            if (bit6) {
                // LD *,* (8 bit)
                const value = self.readReg(block1);
                self.writeReg(block2, value);
                return regCost(block1) + regCost(block2);
            } else {
                return switch (block1) {
                    0 => switch (block2) {
                        // NOP
                        0 => 1,
                        // LD (nn),SP
                        1 => blk: {
                            self.SP = self.readPC16();
                            break :blk 5;
                        },
                        // STOP
                        2 => blk: {
                            self.PC += 1;
                            self.RunState = .STOP;
                            break :blk 0;
                        },
                        // JR
                        3 => blk: {
                            self.jumpRel();
                            break :blk 2;
                        },
                        else => blk: {
                            // JR NZ/NC/Z/C
                            if (self.cond(inst))
                                self.jumpRel();
                            break :blk 2;
                        },
                    },
                    1 => blk: {
                        // LD *,nn (16 bit)
                        const regPtr = self.regPtr16(inst);
                        if ((block2 & 1) == 0) {
                            regPtr.* = self.readPC16();
                        } else {
                            self.R.u16.HL = self.add16(self.R.u16.HL, regPtr.*, true);
                        }
                        break :blk 3;
                    },
                    2 => blk: {
                        // LD (*),A / LD A,(*) / LDI / LDD
                        const selector: u2 = @intCast((inst & 0b110000) >> 4);
                        const regPtr: struct { a: *u16, b: i16 } = switch (selector) {
                            0 => .{ .a = &self.R.u16.BC, .b = 0 },
                            1 => .{ .a = &self.R.u16.DE, .b = 0 },
                            2 => .{ .a = &self.R.u16.HL, .b = 1 },
                            3 => .{ .a = &self.R.u16.HL, .b = -1 },
                        };
                        if (!bit0) {
                            self.write(regPtr.a.*, self.R.u8.A);
                        } else {
                            self.R.u8.A = self.read(regPtr.a.*);
                        }
                        regPtr.a.* +%= @bitCast(regPtr.b);
                        break :blk 2;
                    },
                    3 => blk: {
                        // INC * / DEC * (16 bit)
                        const regPtr = self.regPtr16(inst);
                        const incr: i16 = if (!bit3) 1 else -1;
                        regPtr.* +%= @bitCast(incr);
                        break :blk 2;
                    },
                    4, 5 => blk: {
                        // INC * / DEC * (8 bit)
                        const incr: i8 = if (!bit0) 1 else -1;
                        self.writeReg(block2, self.add(self.readReg(block2), @bitCast(incr), 0, false));
                        break :blk if (block2 == 6) 3 else 1;
                    },
                    6 => blk: {
                        // LD *,n (8 bit)
                        self.writeReg(block2, self.readPC());
                        break :blk regCost(block2) + 1;
                    },
                    7 => switch (block1) {
                        else => blk: {
                            // RLCA, RRCA, RLA, RRA
                            self.R.u8.A = self.rotate(@truncate(block1), self.R.u8.A);
                            break :blk 1;
                        },
                        4 => blk: {
                            // DAA
                            const a = self.R.u8.A;
                            const rem = a % 10;
                            const div = a / 10;
                            self.R.u8.A = (div << 4) | rem;
                            self.R.u8.F.C = div > 9;
                            self.R.u8.F.H = false;
                            self.R.u8.F.Z = a == 0;
                            break :blk 1;
                        },
                        5 => blk: {
                            // CPL
                            self.R.u8.A = @bitReverse(self.R.u8.A);
                            self.R.u8.F.N = true;
                            self.R.u8.F.H = true;
                            break :blk 1;
                        },
                        6 => blk: {
                            // SCF
                            self.R.u8.F.N = false;
                            self.R.u8.F.H = false;
                            self.R.u8.F.C = true;
                            break :blk 1;
                        },
                        7 => blk: {
                            // CCF
                            self.R.u8.F.N = false;
                            self.R.u8.F.H = false;
                            self.R.u8.F.C = !self.R.u8.F.C;
                            break :blk 1;
                        },
                    }
                };
            }
        } else {
            if (!bit6 or isImmediate) {
                // ADD, ADC, SUB, SBC, AND, XOR, OR, CP (8 bit, immediate or register)
                const value = if (!bit6) self.readReg(block1) else self.readPC();
                switch (block2) {
                    0 => self.R.u8.A = self.add(self.R.u8.A, value, 0, true),
                    1 => self.R.u8.A = self.add(self.R.u8.A, value, if (self.R.u8.F.C) 1 else 0, true),
                    2 => self.R.u8.A = self.add(self.R.u8.A, -%value, 0, true),
                    3 => self.R.u8.A = self.add(self.R.u8.A, -%value, if (self.R.u8.F.C) 1 else 0, true),
                    4 => self.R.u8.A = self.flags(self.R.u8.A & value, true, false),
                    5 => self.R.u8.A = self.flags(self.R.u8.A ^ value, false, false),
                    6 => self.R.u8.A = self.flags(self.R.u8.A | value, false, false),
                    7 => _ = self.add(self.R.u8.A, -%value, 0, true),
                }
                return if (!bit6) regCost(block1) else 2;
            } else {
                const ret: u8 = switch (block1) {
                    0 => switch (block2) {
                        else => blk: {
                            // RET NZ/NC/Z/C
                            if (self.cond(inst)) {
                                self.PC = self.pop();
                            }
                            break :blk 2;
                        },
                        // LD (n),A
                        4 => blk: {
                            self.write(0xFF00 + @as(u16, self.readPC()), self.R.u8.A);
                            break :blk 3;
                        },
                        // LD A,(n)
                        5 => blk: {
                            self.R.u8.A = self.read(0xFF00 + @as(u16, self.readPC()));
                            break :blk 3;
                        },
                        // ADD SP,n
                        6 => blk: {
                            const offset = self.readPC();
                            self.SP = self.add16(self.SP, offset, false);
                            break :blk 4;
                        },
                        // LDHL SP,n
                        7 => blk: {
                            const offset = self.readPC();
                            self.R.u16.HL = self.add16(self.SP, offset, false);
                            break :blk 3;
                        },
                    },
                    1 => switch (block2) {
                        else => blk: {
                            // POP *
                            const value = self.pop();
                            const selector: u2 = @intCast((inst & 0b110000) >> 4);
                            switch (selector) {
                                0 => self.R.u16.BC = value,
                                1 => self.R.u16.DE = value,
                                2 => self.R.u16.HL = value,
                                3 => self.R.u16.AF = value,
                            }
                            break :blk 3;
                        },
                        1 => blk: {
                            // RET
                            self.PC = self.pop();
                            break :blk 2;
                        },
                        3 => blk: {
                            // RETI
                            self.IME = true;
                            self.PC = self.pop();
                            break :blk 2;
                        },
                        5 => blk: {
                            // JP (HL)
                            self.PC = self.readU16(self.R.u16.HL);
                            break :blk 1;
                        },
                        7 => blk: {
                            // LD SP,HL
                            self.SP = self.R.u16.HL;
                            break :blk 2;
                        },
                    },
                    2 => switch (block2) {
                        else => blk: {
                            // JP NZ/NC/Z/C
                            if (self.cond(inst)) {
                                self.PC = self.readPC16();
                            }
                            break :blk 3;
                        },
                        // LD (C),A
                        4 => blk: {
                            self.write(0xFF00 + @as(u16, self.R.u8.C), self.R.u8.A);
                            break :blk 2;
                        },
                        // LD (nn),A
                        5 => blk: {
                            self.write(self.readPC16(), self.R.u8.A);
                            break :blk 4;
                        },
                        // LD A,(C)
                        6 => blk: {
                            self.R.u8.A = self.read(0xFF00 + @as(u16, self.R.u8.C));
                            break :blk 2;
                        },
                        // LD A,(nn)
                        7 => blk: {
                            self.R.u8.A = self.read(self.readPC16());
                            break :blk 4;
                        },
                    },
                    3 => switch (block2) {
                        // JP nn
                        0 => blk: {
                            self.PC = self.readPC16();
                            break :blk 3;
                        },
                        // 0xCB opcodes
                        1 => self.opExtra(),
                        else => blk: {
                            self.Error = .InvalidOpcode;
                            break :blk 0;
                        },
                        // DI
                        6 => blk: {
                            self.IME = false;
                            break :blk 1;
                        },
                        // EI
                        7 => blk: {
                            self.IME = true;
                            break :blk 1;
                        },
                    },
                    4 => switch (block2) {
                        0 ... 3 => blk: {
                            // CALL NZ/NC/Z/C
                            if (self.cond(inst)) {
                                self.push(self.PC);
                                self.PC = self.readPC16();
                            }
                            break :blk 3;
                        },
                        else => blk: {
                            self.Error = .InvalidOpcode;
                            break :blk 0;
                        }
                    },
                    5 => if (bit4) blk: {
                        // CALL
                        self.push(self.PC);
                        self.PC = self.readPC16();
                        break :blk 3;
                    } else blk: {
                        // PUSH
                        const selector: u2 = @intCast((inst & 0b110000) >> 4);
                        self.push(switch (selector) {
                            0 => self.R.u16.BC,
                            1 => self.R.u16.DE,
                            2 => self.R.u16.HL,
                            3 => self.R.u16.AF
                        });
                        break :blk 3;
                    },
                    6 => unreachable,
                    7 => blk: {
                        // RST
                        self.push(self.PC);
                        self.PC = @as(u16, block2) << 3;
                        break :blk 8;
                    }
                };
                return ret;
            }
        }
    }

    fn opExtra(self: *GameState) u8 {
        const inst = self.readPC();
        const reg: u3 = @truncate(inst);
        const value = self.readReg(reg);
        const cost = regCost(reg) * 2;
        const bit: u8 = @as(u8, 1) << @intCast((inst & 0b111000) >> 3);
        const block1: u2 = @intCast((inst & 0b11000000) >> 6);
        const block2: u3 = @intCast((inst & 0b00111000) >> 3);
        const newValue = switch (block1) {
            0 => switch (block2) {
                // RLC, RRC, RL, RR
                else => self.rotate(@truncate(inst), value),
                // SLA
                4 => self.flags(value << 1, false, (value & 0x80) != 0),
                // SRA
                5 => self.flags((value >> 1) | (value & 0x80), false, (value & 1) != 0),
                // SWAP
                6 => self.flags((value >> 4) | (value << 4), false, false),
                // SRL
                7 => self.flags((value >> 1), false, (value & 1) != 0),
            },
            1 => {
                // BIT
                self.R.u8.F.Z = (value & bit) == 0;
                self.R.u8.F.N = false;
                self.R.u8.F.H = true;
                return cost;
            },
            // RES
            2 => value & ~bit,
            // SET
            3 => value | bit,
        };
        self.writeReg(reg, newValue);
        return cost;
    }

    fn mainLoop(self: *GameState) void {
        while (true) {
            const canDoInterrupts = switch (self.RunState) {
                .Running => true,
                .HALT => self.IOPorts.IF.Button,
                .STOP => false,
            };
            if (self.IME and canDoInterrupts) {
                const IF: u8 = @bitCast(self.IOPorts.IF);
                const IE: u8 = self.HiRAM[0x7F];
                const interruptsN = IF & IE & 0b11111;
                const interrupts: InterruptFlags = @bitCast(interruptsN);
                if (interruptsN != 0) {
                    self.IME = false;
                    self.IOPorts.IF = @bitCast(@as(u8, 0));
                    self.push(self.PC);
                    self.PC = if (interrupts.VBlank) 0x40
                        else if (interrupts.LCDC) 0x48
                        else if (interrupts.Timer) 0x50
                        else if (interrupts.SerialIO) 0x58
                        else if (interrupts.Button) 0x60
                        else unreachable;
                }
                self.Time.Current += 20;
            }
            while (self.RunState == .Running and self.Time.NextInstruction < self.Time.LCD) {
                self.Time.Current = @max(self.Time.Current, self.Time.NextInstruction);
                self.Time.NextInstruction = self.Time.Current + self.opMain() * 4;
            }
            self.Time.Current = @max(self.Time.Current, self.Time.LCD);
            if (self.IOPorts.LCDC.LCDEnable) {
                switch (self.IOPorts.STAT.Mode) {
                    .HBlank => {
                        self.IOPorts.LY += 1;
                        if (self.IOPorts.LY >= 144) {
                            self.IOPorts.IF.VBlank = true;
                            self.IOPorts.STAT.Mode = .VBlank;
                            if (self.IOPorts.STAT.InterruptEnable.VBlank)
                                self.IOPorts.IF.LCDC = true;
                            self.Time.LCD += 456;
                            return;
                        } else {
                            self.IOPorts.STAT.Mode = .OAMRead;
                            if (self.IOPorts.STAT.InterruptEnable.OAMRead)
                                self.IOPorts.IF.LCDC = true;
                            self.Time.LCD += 80;
                        }
                    },
                    .VBlank => {
                        if (self.IOPorts.LY >= 153) {
                            self.IOPorts.LY = 0;
                            self.IOPorts.STAT.Mode = .OAMRead;
                            if (self.IOPorts.STAT.InterruptEnable.OAMRead)
                                self.IOPorts.IF.LCDC = true;
                            self.Time.LCD += 80;
                        } else {
                            self.IOPorts.LY += 1;
                            self.Time.LCD += 456;
                        }
                    },
                    .OAMRead => {
                        self.IOPorts.STAT.Mode = .Transfer;
                        self.Time.LCD += 172;
                    },
                    .Transfer => {
                        self.drawLine();
                        self.IOPorts.STAT.Mode = .HBlank;
                        if (self.IOPorts.STAT.InterruptEnable.HBlank)
                            self.IOPorts.IF.LCDC = true;
                        self.Time.LCD += 204;
                    },
                }
            } else {
                self.IOPorts.STAT.Mode = .VBlank;
                self.Time.LCD += 70224;
                return;
            }
            if (self.IOPorts.LY == self.IOPorts.LYC and self.IOPorts.STAT.InterruptEnable.LYCCoincidence) {
                self.IOPorts.IF.LCDC = true;
            }
        }
    }
    
    const Vec2 = @Vector(2, i16);

    fn renderTile(self: *GameState, tileIdx: u8, offset: Vec2, tileData: TileDataFlag, palette: Palette) u2 {
        const tile = self.VRAM.Data[if (tileData == .x80) tileIdx else ((tileIdx ^ 0x80) + 0x80)];
        const tileRow = tile[@intCast(offset[1])];
        const tileCol: u4 = @intCast(offset[0]);
        const rawColor = ((tileRow >> (7 - tileCol)) & 1) | (((tileRow >> (15 - tileCol)) & 1) << 1);
        return palette.get(rawColor);
    }

    fn renderTileMap(self: *GameState, pos: Vec2, tileMap: u1, tileData: TileDataFlag) u2 {
        const tilePos = pos >> @as(Vec2, @splat(3));
        const tileOffset = pos & @as(Vec2, @splat(0b111));
        const tileIdx = self.VRAM.Map[tileMap][@intCast(tilePos[1])][@intCast(tilePos[0])];
        return self.renderTile(tileIdx, tileOffset, tileData, self.IOPorts.BGP);
    }

    fn renderSprite(self: *GameState, spriteTile: u8, offset: Vec2, palette: [4]u2) u2 {
        return self.renderTile(
            spriteTile,
            offset,
            1,
            palette
        );
    }

    fn spriteCmp(self: *GameState, a: u8, b: u8) bool {
        const spriteA = self.OAM[a];
        const spriteB = self.OAM[b];
        return if (spriteA.X == spriteB.X) a > b else spriteA.X > spriteB.X;
    }

    fn drawLine(self: *GameState) void {
        const scroll = Vec2{ self.IOPorts.SCX, self.IOPorts.SCY };
        const wndPos = Vec2{ self.IOPorts.WX, self.IOPorts.WY };
        const tallSprites = self.IOPorts.LCDC.SpriteSize == .S8x16;
        var lineSprites: [40]u8 = undefined;
        for (&lineSprites, 0..) |*s, i| {
            s.* = @intCast(40 - 1 - i);
        }
        std.sort.heap(u8, &lineSprites, self, spriteCmp);
        const y = self.IOPorts.LY;
        for (&self.Screen[y], 0..) |*pixel, x| {
            var color: u2 = 0;
            const screenPos = Vec2{ @intCast(x), @intCast(y) };
            if (self.IOPorts.LCDC.BGEnable) {
                color = self.renderTileMap(
                    screenPos +% scroll,
                    self.IOPorts.LCDC.BGTileMap,
                    self.IOPorts.LCDC.BGWindowTileData
                );
            }
            if (self.IOPorts.LCDC.WindowEnable
                and wndPos[0] <= 166
                and wndPos[1] <= 143
                and screenPos[0] >= wndPos[0]
                and screenPos[1] >= wndPos[1]
            ) {
                color = self.renderTileMap(
                    screenPos -% wndPos,
                    self.IOPorts.LCDC.WindowTileMap,
                    self.IOPorts.LCDC.BGWindowTileData
                );
            }
            for (lineSprites) |idx| {
                const sprite = self.OAM[idx];
                const spritePos = Vec2{ sprite.X, sprite.Y };
                var spriteRelPos = screenPos - spritePos - Vec2{ 8, 16 };
                const palette = switch (sprite.Flags.Palette) {
                    .OBJ0PAL => self.IOPorts.OBP0,
                    .OBJ1PAL => self.IOPorts.OBP1,
                };
                if ((sprite.Flags.Priority == 0 or color == 0)
                    and spriteRelPos[0] >= 0
                    and spriteRelPos[0] < 8
                    and spriteRelPos[1] >= 0
                ) {
                    if (sprite.Flags.XFlip) {
                        spriteRelPos[0] ^= 0b111;
                    }
                    if (sprite.Flags.YFlip) {
                        spriteRelPos[1] ^= if (tallSprites) 0b1111 else 0b111;
                    }
                    const spriteColor = if (spriteRelPos[1] < 8)
                        self.renderTile(
                            if (tallSprites) sprite.Tile & 0xFE else sprite.Tile,
                            spriteRelPos,
                            .x80,
                            palette
                        )
                    else if (tallSprites and spriteRelPos[1] < 16)
                        self.renderTile(
                            sprite.Tile | 1,
                            spriteRelPos - Vec2{ 0, 8 },
                            .x80,
                            palette
                        )
                    else 0;
                    if (spriteColor != 0) {
                        color = spriteColor;
                    }
                }
            }
            pixel.* = color;
        }
    }

    fn audio(self: *GameState) void {
        const NR52 = &self.IOPorts.NR52;
        if (!NR52.SoundEnable) {
            return;
        }

        const Audio = &self.Audio;
        const div2 = Audio.DIVAPU & 1 == 0 and Audio.DIVAPUPrev & 1 != 0;
        const div4 = Audio.DIVAPU & 2 == 0 and Audio.DIVAPUPrev & 2 != 0;
        const div8 = Audio.DIVAPU & 4 == 0 and Audio.DIVAPUPrev & 4 != 0;
        self.Audio.DIVAPUPrev = Audio.DIVAPU;

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
                if (Audio.C1Length >= 63) {
                    NR52.C1Active = false;
                    Audio.Outputs[0] = 0;
                } else {
                    Audio.C1Length += 1;
                }
            }

            if (NR10.SweepPace > 0 and div4) {
                if (Audio.C1Sweep <= 1) {
                    Audio.C1Sweep = NR10.SweepPace;
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
                    Audio.C1Sweep -= 1;
                }
            }

            if (Sound1.EnvelopeSweep > 0 and div8) {
                Audio.C1VolumeSweep +%= 1;
                if (Audio.C1VolumeSweep >= Sound1.EnvelopeSweep) {
                    Audio.C1VolumeSweep = 0;
                    switch (Sound1.EnvelopeDirection) {
                        1 => if (Sound1.Volume < 15) { Sound1.Volume += 1; },
                        0 => if (Sound1.Volume > 0) { Sound1.Volume -= 1; },
                    }
                }
            }

            Audio.C1Period +%= 1;
            if (Audio.C1Period == 0) {
                Audio.C1Period = Sound1.Period;
                Audio.C1Sample +%= 1;
            }
            
            const waveform = pulseWaveforms[Sound1.WaveDuty];
            Audio.Outputs[0] = if (waveform >> Audio.C1Sample != 0) Sound1.Volume else 0;
        }

        if (doPulse and NR52.C2Active) {
            const Sound2 = &self.IOPorts.Sound2;

            if (Sound2.LengthEnable and div2) {
                if (Audio.C2Length >= 63) {
                    NR52.C2Active = false;
                    Audio.Outputs[1] = 0;
                } else {
                    Audio.C2Length += 1;
                }
            }

            if (Sound2.EnvelopeSweep > 0 and div8) {
                Audio.C2VolumeSweep +%= 1;
                if (Audio.C2VolumeSweep >= Sound2.EnvelopeSweep) {
                    Audio.C2VolumeSweep = 0;
                    switch (Sound2.EnvelopeDirection) {
                        1 => if (Sound2.Volume < 15) { Sound2.Volume += 1; },
                        0 => if (Sound2.Volume > 0) { Sound2.Volume -= 1; },
                    }
                }
            }

            Audio.C2Period +%= 1;
            if (Audio.C2Period == 0) {
                Audio.C2Period = Sound2.Period;
                Audio.C2Sample +%= 1;
            }
            
            const waveform = pulseWaveforms[Sound2.WaveDuty];
            Audio.Outputs[1] = if (waveform >> Audio.C1Sample != 0) Sound2.Volume else 0;
        }

        if (doWave and NR52.C3Active and self.IOPorts.NR30.Enable) {
            const Sound3 = &self.IOPorts.Sound3;

            if (Sound3.LengthEnable and div2) {
                if (Audio.C3Length >= 255) {
                    NR52.C3Active = false;
                    Audio.Outputs[2] = 0;
                } else {
                    Audio.C3Length += 1;
                }
            }

            Audio.C3Period +%= 1;
            if (Audio.C3Period == 0) {
                Audio.C3Period = Sound3.Period;
                Audio.C3Sample +%= 1;
            }
            
            const shift = if (Sound3.Volume == 0) 4 else (Sound3.Volume - 1);
            Audio.Outputs[2] = self.IOPorts.WavePattern.get(Audio.C3Sample ^ 0b1) >> shift;
        }

        if (NR52.C4Active) {
            const Sound4 = &self.IOPorts.Sound4;

            if (Sound4.LengthEnable and div2) {
                if (Audio.C4Length >= 63) {
                    NR52.C4Active = false;
                    Audio.Outputs[3] = 0;
                } else {
                    Audio.C4Length += 1;
                }
            }

            if (Sound4.EnvelopeSweep > 0 and div8) {
                Audio.C4VolumeSweep +%= 1;
                if (Audio.C4VolumeSweep >= Sound4.EnvelopeSweep) {
                    Audio.C4VolumeSweep = 0;
                    switch (Sound4.EnvelopeDirection) {
                        1 => if (Sound4.Volume < 15) { Sound4.Volume += 1; },
                        0 => if (Sound4.Volume > 0) { Sound4.Volume -= 1; },
                    }
                }
            }

            Audio.C4Period +%= 1;
            if (Audio.C4Period == 0) {
                Audio.C4Period = Sound4.Freq;
                Audio.C4Sample +%= 1;
            }
        }

        const NR50 = &self.IOPorts.NR50;
        const NR51 = &self.IOPorts.NR51;
        var s0: u16 = 0;
        var s1: u16 = 0;
        inline for (0..4) |i| {
            s0 += if((NR51.S01Channels & (1 << i)) != 0) Audio.Outputs[i] * (NR50.S01Volume + 1) else 0;
            s1 += if((NR51.S02Channels & (1 << i)) != 0) Audio.Outputs[i] * (NR50.S01Volume + 1) else 0;
        }

        Audio.SampleBuffer[Audio.SampleBufferIdx] = .{ s0, s1 };
        Audio.SampleBufferIdx += 1;
        
        if (Audio.SampleBufferIdx >= Audio.SampleBuffer.len) {
            Audio.SampleBufferIdx = 0;
            // channel output * max volume * number of channels * buffer size
            const MaxValue = 0xF * 8 * 4 * Audio.SampleBuffer.len;
            var avg: @Vector(2, u32) = .{ 0, 0 };
            for (0..Audio.SampleBuffer.len) |i| {
                avg += Audio.SampleBuffer[i];
            }
            AudioRingBuffer.write(.{ avg[0] / MaxValue, avg[1] / MaxValue });
        }
    }
};
// zig fmt: on

fn soundioCall(err: c_int) !void {
    if (err != 0) {
        std.debug.print("{s}\n", .{C.soundio_strerror(err)});
        return error.AudioError;
    }
}

fn writeCallback(outStream: [*c]C.SoundIoOutStream, frameCountMin: c_int, frameCountMax: c_int) callconv(.C) void {
    _ = frameCountMin;
    const layout = outStream.*.layout;

    const available: c_int = @intCast(AudioRingBuffer.count());
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
            if (!AudioRingBuffer.read(&value)) {
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

const BootROM = @embedFile("DMG_ROM.bin");

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
var AudioRingBuffer: RingBuffer(f32, 2, SampleRate / 50) = .{};

pub fn main() !void {
    // if (C.glfwInit() == 0) return error.NoGLFW;
    // const window = C.glfwCreateWindow(160, 144, "Gameboy", null, null) orelse return error.OutOfMemory;
    // C.glfwMakeContextCurrent(window);
    // defer C.glfwTerminate();

    const soundIo: *C.struct_SoundIo = C.soundio_create() orelse return error.AudioError;
    try soundioCall(C.soundio_connect(soundIo));
    C.soundio_flush_events(soundIo);
    const deviceIdx = C.soundio_default_output_device_index(soundIo);
    if (deviceIdx < 0) {
        return error.NoAudioDevice;
    }
    const device: *C.struct_SoundIoDevice = C.soundio_get_output_device(soundIo, deviceIdx) orelse return error.AudioError;
    const outStream: *C.struct_SoundIoOutStream = C.soundio_outstream_create(device) orelse return error.AudioError;
    outStream.format = C.SoundIoFormatFloat32NE;
    outStream.format = SampleRate;
    outStream.layout = C.soundio_channel_layout_get_builtin(C.SoundIoChannelLayoutIdStereo).*;
    outStream.write_callback = writeCallback;
    try soundioCall(C.soundio_outstream_open(outStream));
    try soundioCall(C.soundio_outstream_start(outStream));
    defer {
        C.soundio_outstream_destroy(outStream);
        C.soundio_device_unref(device);
        C.soundio_destroy(soundIo);
    }

    var state: GameState = undefined;
    @memset(asBytes(GameState, &state), 0);
    @memset(asBytes(VRAM, &state.VRAM), 0xFF);
    state.ROM = BootROM;
    while (true) {
        state.mainLoop();
    }

    // var color: u8 = 0;
    // while (C.glfwWindowShouldClose(window) == 0) {
    //     color +%= 1;
    //     // clear to red
    //     C.glClearColor(@as(C.GLclampf, @floatFromInt(color)) / 255.0, 0.0, 0.0, 1.0);
    //     C.glClear(C.GL_COLOR_BUFFER_BIT);

    //     C.glfwSwapBuffers(window);
    //     C.glfwPollEvents();
    //     state.mainLoop();
    // }
}
