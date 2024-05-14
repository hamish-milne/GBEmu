const std = @import("std");

pub const InterruptFlags = packed struct {
    VBlank: bool,
    LCDC: bool,
    Timer: bool,
    SerialIO: bool,
    Button: bool,
    _: u3,
};

pub const Palette = std.PackedIntArray(u2, 4);
pub const WavePattern = std.PackedIntArray(u4, 32);

pub fn asBytes(comptime T: type, value: *T) *[@sizeOf(T)]u8 {
    return @as([*]u8, @ptrCast(value))[0..@sizeOf(T)];
}

pub const IOPorts = extern struct {
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
        InitialVolume: u4,
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
        InitialVolume: u4,
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
        InitialVolume: u2,
        _2: u1,
        // NR33..34
        Period: u11,
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
        Volume: u4,
        // NR43
        FreqDiv: u3,
        Step: u1,
        Freq: u4,
        // NR44
        _1: u6,
        LengthEnable: bool,
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
    WavePattern: [16]u8 align(1),
    LCDC: packed struct {
        BGEnable: bool,
        SpriteEnable: bool,
        TallSprites: bool,
        BGTileMap: u1,
        BGUseObjData: bool,
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
    BGP: u8 align(1),
    OBP0: u8 align(1),
    OBP1: u8 align(1),
    WY: u8 align(1),
    WX: u8 align(1),
    _5: u8 align(1),
    SPEED: u8 align(1),
    // _5: u32 align(1),
    // BOOT: packed struct {
    //     BOOT: bool,
    //     _: u7,
    // } align(1),
};

const WriteMask: IOPorts = .{
    .P1 = 0b00110000,
    .SB = 0xff,
    .SC = 0b10000001,
    ._ = 0,
    .DIV = 0,
    .TIMA = 0xff,
    .TMA = 0xff,
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
    .NR10 = 0xff,
    .Sound1 = .{
        .SoundLength = 0b111111,
        .WaveDuty = 0b11,
        .EnvelopeSweep = 0b111,
        .EnvelopeDirection = 0b1,
        .InitialVolume = 0b1111,
        .Period = 0b11111111111,
        ._1 = 0b111,
        .LengthEnable = true,
        .Initial = true,
    },
    ._2 = 0,
    .Sound2 = .{
        .SoundLength = 0b111111,
        .WaveDuty = 0b11,
        .EnvelopeSweep = 0b111,
        .EnvelopeDirection = 0b1,
        .InitialVolume = 0b1111,
        .Period = 0b11111111111,
        ._ = 0b111,
        .LengthEnable = true,
        .Initial = true,
    },
    .NR30 = .{
        ._ = 0b1111111,
        .Enable = true,
    },
    .Sound3 = .{
        .Length = 0b11111111,
        ._1 = 0b11111,
        .InitialVolume = 0b11,
        ._2 = 0b1,
        .Period = 0b11111111111,
        ._3 = 0b111,
        .LengthEnable = true,
        .Initial = true,
    },
    ._3 = 0,
    .Sound4 = .{
        .SoundLength = 0b111111,
        ._ = 0b11,
        .EnvelopeSweep = 0b111,
        .EnvelopeDirection = 0b1,
        .Volume = 0b1111,
        .FreqDiv = 0b111,
        .Step = 0b1,
        .Freq = 0b1111,
        ._1 = 0b111111,
        .LengthEnable = true,
        .Initial = true,
    },
    .NR50 = .{
        .S01Volume = 0b111,
        .S01Vin = true,
        .S02Volume = 0b111,
        .S02Vin = true,
    },
    .NR51 = .{
        .S01Channels = 0b1111,
        .S02Channels = 0b1111,
    },
    .NR52 = .{
        .C1Active = true,
        .C2Active = true,
        .C3Active = true,
        .C4Active = true,
        ._ = 0b111,
        .SoundEnable = true,
    },
    ._4 = .{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    .WavePattern = [16]u8{
        0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff,
    },
    .LCDC = .{
        .BGEnable = true,
        .SpriteEnable = true,
        .TallSprites = true,
        .BGTileMap = 0b1,
        .BGUseObjData = true,
        .WindowEnable = true,
        .WindowTileMap = 0b1,
        .LCDEnable = true,
    },
    .STAT = .{
        .Mode = @bitCast(0),
        .LYCCoincidence = false,
        .InterruptEnable = .{
            .HBlank = true,
            .VBlank = true,
            .OAMRead = true,
            .LYCCoincidence = true,
        },
        ._ = 0,
    },
    .SCY = 0xff,
    .SCX = 0xff,
    .LY = 0,
    .LYC = 0xff,
    .DMA = 0xff,
    .BGP = 0xff,
    .OBP0 = 0xff,
    .OBP1 = 0xff,
    .WY = 0xff,
    .WX = 0xff,
    ._5 = 0,
    .SPEED = 0xff,
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
    // if (@sizeOf(IOPorts) != 0x51) {
    //     unreachable;
    // }
    if (@sizeOf(VRAM) != 0x2000) {
        unreachable;
    }
    if (@sizeOf(OAM) != 0xA0) {
        unreachable;
    }
}

pub const Memory = struct {
    IOPorts: IOPorts,
    HiRAM: [0x80]u8,
    OAM: OAM,
    IntRAM: [0x2000]u8,
    VRAM: VRAM,
    MBC: union(enum) {
        // zig fmt: off
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
        // zig fmt: on
    },
    BootROM: []const u8,
    ROM: []const u8,
    BootROMEnabled: bool,

    pub fn setMBC(
        self: *Memory,
    ) void {
        self.BootROMEnabled = true;
        switch (self.ROM[0x147]) {
            0x00 => self.MBC = .ROMOnly,
            0x01...0x03 => self.MBC = .{ .MBC1 = .{
                .ROMBank = 1,
                .RAMBank = .{
                    .RAMBankSel = 0,
                },
                .RAMEnable = false,
                .Data = undefined,
            } },
            0x05...0x06 => self.MBC = .{ .MBC2 = .{
                .ROMBank = 1,
                .RAMEnable = false,
                .Data = undefined,
            } },
            0x0F...0x13 => self.MBC = .{ .MBC3 = .{
                .ROMBank = 1,
                .RAMBank = 0,
                .RAMEnable = false,
                .Data = undefined,
            } },
            0x19...0x1E => self.MBC = .{ .MBC5 = .{
                .ROMBank = 1,
                .RAMBank = 0,
                .RAMEnable = false,
                .Data = undefined,
            } },
            else => unreachable,
        }
    }

    pub fn read(self: *Memory, addr: u16) u8 {
        const topNibble: u4 = @intCast((addr & 0xF000) >> 12);
        return switch (topNibble) {
            0x0...0x3 => if (self.BootROMEnabled and addr < self.BootROM.len)
                self.BootROM[addr]
            else if (addr < self.ROM.len)
                self.ROM[addr]
            else
                0,
            0x4...0x7 => blk: {
                const romBank = switch (self.MBC) {
                    .ROMOnly => 0,
                    .MBC1 => |mbc1| mbc1.ROMBank | switch (mbc1.RAMBank) {
                        .ROMBankSel => |upper| @as(u8, upper) << 5,
                        else => 0,
                    },
                    .MBC2 => |mbc2| mbc2.ROMBank,
                    .MBC3 => |mbc3| mbc3.ROMBank,
                    .MBC5 => |mbc5| mbc5.ROMBank,
                };
                const bank: u32 = if (romBank == 0) 1 else romBank;
                const fullAddr = (bank << 14) | (addr & 0x3FFF);
                break :blk if (fullAddr >= self.ROM.len) 0 else self.ROM[fullAddr];
            },
            0x8...0x9 => asBytes(VRAM, &self.VRAM)[addr & 0x1FFF],
            0xA...0xB => switch (self.MBC) {
                .ROMOnly => 0,
                .MBC1 => |mbc1| if (mbc1.RAMEnable) switch (mbc1.RAMBank) {
                    .RAMBankSel => |ramBank| mbc1.Data[ramBank][addr & 0x1FFF],
                    else => 0,
                } else 0,
                .MBC2 => |mbc2| if (mbc2.RAMEnable) mbc2.Data[addr & 0xFF] else 0,
                .MBC3 => |mbc3| if (mbc3.RAMEnable) mbc3.Data[mbc3.RAMBank][addr & 0x1FFF] else 0,
                .MBC5 => |mbc5| if (mbc5.RAMEnable) mbc5.Data[mbc5.RAMBank][addr & 0x1FFF] else 0,
            },
            0xC...0xE => self.IntRAM[addr & 0x1FFF],
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
                else => self.IntRAM[addr & 0x1FFF],
            },
        };
    }

    pub fn write(self: *Memory, addr: u16, value: u8) void {
        const topNibble: u4 = @intCast((addr & 0xF000) >> 12);
        switch (topNibble) {
            0x0...0x1 => {
                const enable = (value & 0b1111) == 0b1010;
                switch (self.MBC) {
                    .MBC1 => |*mbc1| mbc1.RAMEnable = enable,
                    .MBC2 => |*mbc2| if (addr & 0x0100 != 0) {
                        mbc2.RAMEnable = enable;
                    },
                    .MBC3 => |*mbc3| mbc3.RAMEnable = enable,
                    .MBC5 => |*mbc5| mbc5.RAMEnable = enable,
                    else => {},
                }
            },
            0x2...0x3 => {
                switch (self.MBC) {
                    .MBC1 => |*mbc1| mbc1.ROMBank = @truncate(value),
                    .MBC2 => |*mbc2| if (addr & 0x0100 == 0) {
                        mbc2.ROMBank = @truncate(value);
                    },
                    .MBC3 => |*mbc3| mbc3.ROMBank = @truncate(value),
                    .MBC5 => |*mbc5| if (addr < 0x3000) {
                        mbc5.ROMBank = (mbc5.ROMBank & 0b011111111) | (@as(u9, value & 0b1) << 8);
                    } else {
                        mbc5.ROMBank = (mbc5.ROMBank & 0b100000000) | value;
                    },
                    else => {},
                }
            },
            0x4...0x5 => {
                switch (self.MBC) {
                    .MBC1 => |*mbc1| switch (mbc1.RAMBank) {
                        .RAMBankSel => |*ptr| ptr.* = @truncate(value),
                        .ROMBankSel => |*ptr| ptr.* = @truncate(value),
                    },
                    else => {},
                }
            },
            0x6...0x7 => {},
            0x8...0x9 => asBytes(VRAM, &self.VRAM)[addr & 0x1FFF] = value,
            0xA...0xB => switch (self.MBC) {
                .MBC1 => |*mbc1| if (mbc1.RAMEnable) switch (mbc1.RAMBank) {
                    .RAMBankSel => |ramBank| mbc1.Data[ramBank][addr & 0x1FFF] = value,
                    else => {},
                },
                .MBC2 => |*mbc2| if (mbc2.RAMEnable) {
                    mbc2.Data[addr & 0xFF] = value;
                },
                .MBC3 => |*mbc3| if (mbc3.RAMEnable) {
                    mbc3.Data[mbc3.RAMBank][addr & 0x1FFF] = value;
                },
                .MBC5 => |*mbc5| if (mbc5.RAMEnable) {
                    mbc5.Data[mbc5.RAMBank][addr & 0x1FFF] = value;
                },
                else => {},
            },
            0xC...0xE => self.IntRAM[addr & 0x1FFF] = value,
            0xF => switch ((addr & 0x0F00) >> 8) {
                0xE => {
                    const oamBytes = asBytes(OAM, &self.OAM);
                    const localAddr = addr & 0xFF;
                    if (localAddr < oamBytes.len) oamBytes[localAddr] = value;
                },
                0xF => if (addr < 0xFF80) {
                    const ioportsBytes = asBytes(IOPorts, &self.IOPorts);
                    const localAddr = addr & 0xFF;
                    if (localAddr < ioportsBytes.len) {
                        ioportsBytes[localAddr] = value;
                    } else if (localAddr == 0x50 and value != 0) {
                        self.BootROMEnabled = false;
                    }
                } else {
                    self.HiRAM[addr & 0x7f] = value;
                },
                else => self.IntRAM[addr & 0x1FFF] = value,
            },
        }
    }

    pub fn readU16(self: *Memory, addr: u16) u16 {
        return (@as(u16, self.read(addr + 1)) << 8) | self.read(addr);
    }

    pub fn writeU16(self: *Memory, addr: u16, value: u16) void {
        self.write(addr, @truncate(value));
        self.write(addr +% 1, @truncate(value >> 8));
    }
};
