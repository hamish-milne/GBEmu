const std = @import("std");
const memory = @import("memory.zig");
const Memory = memory.Memory;
const InterruptFlags = memory.InterruptFlags;
const graphics = @import("graphics.zig");

// zig fmt: off
pub const CPU = struct {
    RunState: enum {
        Running,
        HALT,
        STOP,
    } = .Running,
    Error: enum {
        None,
        InvalidOpcode,
    } = .None,
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
    IME: bool,
    sc: u32,

    mem: *Memory,

    fn read(self: *CPU, addr: u16) u8 {
        return self.mem.read(addr);
    }

    fn write(self: *CPU, addr: u16, value: u8) void {
        self.mem.write(addr, value);
    }

    fn readU16(self: *CPU, addr: u16) u16 {
        return self.mem.readU16(addr);
    }

    fn writeU16(self: *CPU, addr: u16, value: u16) void {
        self.mem.writeU16(addr, value);
    }

    fn add(self: *CPU, a: u8, b: u8, op: enum { Add, Sub }, carry: enum { None, Set, In }) u8 {
        const c: u1 = switch (carry) {
            .In => if (self.R.u8.F.C) 1 else 0,
            else => 0,
        };
        const c1 = switch (op) {
            .Add => c,
            .Sub => ~c
        };
        const b1: u9 = switch (op) {
            .Add => b,
            .Sub => ~b,
        };
        const a1: u9 = a;
        const result: u9 = a1 + b1 + c1;
        const value: u8 = @truncate(result);
        self.R.u8.F.Z = value == 0;
        self.R.u8.F.N = op == .Sub;
        const resultH = (a1 & 0xF) + (b1 & 0xF) + c1;
        self.R.u8.F.H = switch (op) {
            .Add => resultH & 0b10000 != 0,
            .Sub => resultH & 0b10000 == 0,
        };
        if (carry != .None) {
            self.R.u8.F.C = switch (op) {
                .Add => result & 0b100000000 != 0,
                .Sub => result & 0b010000000 != 0,
            };
        }
        return value;
    }

    fn add16(self: *CPU, a: u16, b: u16, setFlags: bool) u16 {
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

    fn flags(self: *CPU, value: u8, h: bool, c: bool) u8 {
        self.R.u8.F.Z = value == 0;
        self.R.u8.F.N = false;
        self.R.u8.F.H = h;
        self.R.u8.F.C = c;
        return value;
    }

    fn readReg(self: *CPU, selector: u3) u8 {
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

    fn writeReg(self: *CPU, selector: u3, value: u8) void {
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

    fn readPC(self: *CPU) u8 {
        const pc = self.PC;
        self.PC +%= 1;
        return self.read(pc);
    }

    
    fn jumpRel(self: *CPU) void {
        const offset: i8 = @bitCast(self.readPC());
        self.PC +%= @bitCast(@as(i16, offset));
    }

    fn readPC16(self: *CPU) u16 {
        const low = self.readPC();
        const high: u16 = self.readPC();
        return (high << 8) | low;
    }

    fn regPtr16(self: *CPU, inst: u8) *u16 {
        const selector: u2 = @intCast((inst & 0b110000) >> 4);
        return switch (selector) {
            0 => &self.R.u16.BC,
            1 => &self.R.u16.DE,
            2 => &self.R.u16.HL,
            3 => &self.SP,
        };
    }

    fn push(self: *CPU, value: u16) void {
        self.SP -%= 2;
        self.writeU16(self.SP, value);
    }

    fn pop(self: *CPU) u16 {
        const value = self.readU16(self.SP);
        self.SP +%= 2;
        return value;
    }

    fn rotate(self: *CPU, variant: u2, value: u8) u8 {
        const newC = switch (variant) {
            // RLC, RL
            0, 2 => value >> 7,
            // RRC, RR
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

    fn cond(self: *CPU, inst: u8) bool {
        const selector: u2 = @intCast((inst & 0b00011000) >> 3);
        return switch (selector) {
            0 => !self.R.u8.F.Z,
            1 => self.R.u8.F.Z,
            2 => !self.R.u8.F.C,
            3 => self.R.u8.F.C
        };
    }

    pub fn opMain(self: *CPU) u32 {
        const inst = self.readPC();
        const block2: u3 = @intCast((inst & 0b00111000) >> 3);
        const block1: u3 = @intCast(inst & 0b111);
        const bit7 = (inst & 0b10000000) != 0;
        const bit6 = (inst & 0b1000000) != 0;
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
                        0 => 100,
                        // LD (nn),SP
                        1 => blk: {
                            self.writeU16(self.readPC16(), self.SP);
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
                            if (self.cond(inst)) {
                                self.jumpRel();
                            } else {
                                self.PC += 1;
                            }
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
                        if (!bit3) {
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
                        self.writeReg(
                            block2,
                            self.add(self.readReg(block2), 1, if (bit0) .Sub else .Add, .None)
                        );
                        break :blk if (block2 == 6) 3 else 1;
                    },
                    6 => blk: {
                        // LD *,n (8 bit)
                        self.writeReg(block2, self.readPC());
                        break :blk regCost(block2) + 1;
                    },
                    7 => switch (block2) {
                        else => blk: {
                            // RLCA, RRCA, RLA, RRA
                            self.R.u8.A = self.rotate(@intCast(block2), self.R.u8.A);
                            self.R.u8.F.Z = false;
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
                            self.R.u8.A = ~self.R.u8.A;
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
                    0 => self.R.u8.A = self.add(self.R.u8.A, value, .Add, .Set),
                    1 => self.R.u8.A = self.add(self.R.u8.A, value, .Add, .In),
                    2 => self.R.u8.A = self.add(self.R.u8.A, value, .Sub, .Set),
                    3 => self.R.u8.A = self.add(self.R.u8.A, value, .Sub, .In),
                    4 => self.R.u8.A = self.flags(self.R.u8.A & value, true, false),
                    5 => self.R.u8.A = self.flags(self.R.u8.A ^ value, false, false),
                    6 => self.R.u8.A = self.flags(self.R.u8.A | value, false, false),
                    7 => _ = self.add(self.R.u8.A, value, .Sub, .Set),
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
                        6 => blk: {
                            self.R.u8.A = self.read(0xFF00 + @as(u16, self.readPC()));
                            break :blk 3;
                        },
                        // ADD SP,n
                        5 => blk: {
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
                            // JP HL
                            self.PC = self.R.u16.HL;
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
                            } else {
                                self.PC += 2;
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
                                const dst = self.readPC16();
                                self.push(self.PC);
                                self.PC = dst;
                            } else {
                                self.PC += 2;
                            }
                            break :blk 3;
                        },
                        else => blk: {
                            self.Error = .InvalidOpcode;
                            break :blk 0;
                        }
                    },
                    5 => if (bit3) blk: {
                        // CALL
                        const dst = self.readPC16();
                        self.push(self.PC);
                        self.PC = dst;
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

    fn opExtra(self: *CPU) u8 {
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
                else => self.rotate(@intCast(block2), value),
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

    pub fn interrupt(self: *CPU) bool {
        const IOPorts = &self.mem.IOPorts;
        const canDoInterrupts = switch (self.RunState) {
            .Running => true,
            .HALT => IOPorts.IF.Button,
            .STOP => false,
        };
        if (self.IME and canDoInterrupts) {
            const IF: u8 = @bitCast(IOPorts.IF);
            const IE: u8 = self.mem.HiRAM[0x7F];
            const interruptsN = IF & IE & 0b11111;
            const interrupts: memory.InterruptFlags = @bitCast(interruptsN);
            if (interruptsN != 0) {
                self.IME = false;
                IOPorts.IF = @bitCast(@as(u8, 0));
                self.push(self.PC);
                self.PC = if (interrupts.VBlank) 0x40
                    else if (interrupts.LCDC) 0x48
                    else if (interrupts.Timer) 0x50
                    else if (interrupts.SerialIO) 0x58
                    else if (interrupts.Button) 0x60
                    else unreachable;
            }
            return true;
        }
        return false;
    }

};
// zig fmt: on

const CPURegs = struct {
    SP: ?u16 = null,
    PC: ?u16 = null,
    AF: ?u16 = null,
    BC: ?u16 = null,
    DE: ?u16 = null,
    HL: ?u16 = null,
};

const MemorySpec = struct {
    addr: u16,
    initial: ?u8 = null,
    expected: ?u8 = null,
};

const TestSpec = struct {
    input: []const u8,
    initial: ?CPURegs = null,
    expected: CPURegs,
    memory: ?[]const MemorySpec = null,
    state: ?@TypeOf(@as(CPU, undefined).RunState) = null,
    IME: ?bool = null,
};

const expectEqual = std.testing.expectEqual;

fn opcodeTest(t: TestSpec) !void {
    var mem: Memory = undefined;
    var cpu: CPU = undefined;
    @memset(memory.asBytes(Memory, &mem), 0);
    @memset(memory.asBytes(CPU, &cpu), 0);
    if (t.initial) |init| {
        cpu.SP = init.SP orelse 0;
        cpu.PC = init.PC orelse 0;
        cpu.R.u16.AF = init.AF orelse 0;
        cpu.R.u16.BC = init.BC orelse 0;
        cpu.R.u16.DE = init.DE orelse 0;
        cpu.R.u16.HL = init.HL orelse 0;
    }
    if (t.memory) |list| {
        for (list) |item| {
            if (item.initial) |value| {
                mem.write(item.addr, value);
            }
        }
    }
    cpu.mem = &mem;
    mem.ROM = t.input;
    _ = cpu.opMain();
    if (t.expected.SP) |expected| {
        try expectEqual(expected, cpu.SP);
    }
    if (t.expected.PC) |expected| {
        try expectEqual(expected, cpu.PC);
    }
    if (t.expected.AF) |expected| {
        try expectEqual(expected, cpu.R.u16.AF);
    }
    if (t.expected.BC) |expected| {
        try expectEqual(expected, cpu.R.u16.BC);
    }
    if (t.expected.DE) |expected| {
        try expectEqual(expected, cpu.R.u16.DE);
    }
    if (t.expected.HL) |expected| {
        try expectEqual(expected, cpu.R.u16.HL);
    }
    if (t.memory) |list| {
        for (list) |item| {
            if (item.expected) |expected| {
                try expectEqual(expected, mem.read(item.addr));
            }
        }
    }
    if (t.state) |expected| {
        try expectEqual(expected, cpu.RunState);
    }
    if (t.IME) |expected| {
        try expectEqual(expected, cpu.IME);
    }
}

test "NOP" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x00,
        },
        .expected = .{
            .PC = 1,
        },
    });
}

test "LD (nn),SP" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x08, 0x0D, 0xF0,
        },
        .initial = .{
            .SP = 0x1234,
        },
        .expected = .{
            .PC = 3,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .expected = 0x34 },
            .{ .addr = 0xF00E, .expected = 0x12 },
        },
    });
}

test "STOP" {
    try opcodeTest(.{
        .input = &[_]u8{ 0x10, 0x00 },
        .expected = .{
            .PC = 2,
        },
        .state = .STOP,
    });
}

test "JR" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x18, 0x34,
        },
        .expected = .{
            .PC = 0x36,
        },
    });
}

test "JR NZ" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x20, 0x34,
        },
        .initial = .{
            .AF = 1 << 7,
        },
        .expected = .{
            .PC = 2,
        },
    });
}

test "JR Z" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x28, 0x34,
        },
        .initial = .{
            .AF = 1 << 7,
        },
        .expected = .{
            .PC = 0x36,
        },
    });
}

test "JR NC" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x30, 0x34,
        },
        .initial = .{
            .AF = 1 << 4,
        },
        .expected = .{
            .PC = 2,
        },
    });
}

test "JR C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x38, 0x34,
        },
        .initial = .{
            .AF = 1 << 4,
        },
        .expected = .{
            .PC = 0x36,
        },
    });
}

test "LD BC,nn" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x01, 0x34, 0x12,
        },
        .expected = .{
            .PC = 3,
            .BC = 0x1234,
        },
    });
}

test "LD DE,nn" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x11, 0x34, 0x12,
        },
        .expected = .{
            .PC = 3,
            .DE = 0x1234,
        },
    });
}

test "LD HL,nn" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x21, 0x34, 0x12,
        },
        .expected = .{
            .PC = 3,
            .HL = 0x1234,
        },
    });
}

test "LD SP,nn" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x31, 0x34, 0x12,
        },
        .expected = .{
            .PC = 3,
            .SP = 0x1234,
        },
    });
}

test "LD (BC),A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x02,
        },
        .initial = .{
            .BC = 0xF00D,
            .AF = 0x5600,
        },
        .expected = .{
            .PC = 1,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .expected = 0x56 },
        },
    });
}

test "LD (DE),A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x12,
        },
        .initial = .{
            .DE = 0xF00D,
            .AF = 0x5600,
        },
        .expected = .{
            .PC = 1,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .expected = 0x56 },
        },
    });
}

test "LDI (HL),A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x22,
        },
        .initial = .{
            .HL = 0xF00D,
            .AF = 0x5600,
        },
        .expected = .{
            .PC = 1,
            .HL = 0xF00E,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .expected = 0x56 },
        },
    });
}

test "LDD (HL),A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x32,
        },
        .initial = .{
            .HL = 0xF00D,
            .AF = 0x5600,
        },
        .expected = .{
            .PC = 1,
            .HL = 0xF00C,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .expected = 0x56 },
        },
    });
}

test "LD A,(BC)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x0A,
        },
        .initial = .{
            .BC = 0xF00D,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x5600,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .initial = 0x56 },
        },
    });
}

test "LD A,(DE)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x1A,
        },
        .initial = .{
            .DE = 0xF00D,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x5600,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .initial = 0x56 },
        },
    });
}

test "LDI A,(HL)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x2A,
        },
        .initial = .{
            .HL = 0xF00D,
        },
        .expected = .{
            .PC = 1,
            .HL = 0xF00E,
            .AF = 0x5600,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .initial = 0x56 },
        },
    });
}

test "LDD A,(HL)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x3A,
        },
        .initial = .{
            .HL = 0xF00D,
        },
        .expected = .{
            .PC = 1,
            .HL = 0xF00C,
            .AF = 0x5600,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .initial = 0x56 },
        },
    });
}

test "INC BC" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x03,
        },
        .initial = .{
            .BC = 0x1234,
        },
        .expected = .{
            .PC = 1,
            .BC = 0x1235,
        },
    });
}

test "INC DE" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x13,
        },
        .initial = .{
            .DE = 0x1234,
        },
        .expected = .{
            .PC = 1,
            .DE = 0x1235,
        },
    });
}

test "INC HL" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x23,
        },
        .initial = .{
            .HL = 0x1234,
        },
        .expected = .{
            .PC = 1,
            .HL = 0x1235,
        },
    });
}

test "INC SP" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x33,
        },
        .initial = .{
            .SP = 0x1234,
        },
        .expected = .{
            .PC = 1,
            .SP = 0x1235,
        },
    });
}

test "DEC BC" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x0B,
        },
        .initial = .{
            .BC = 0x1234,
        },
        .expected = .{
            .PC = 1,
            .BC = 0x1233,
        },
    });
}

test "DEC DE" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x1B,
        },
        .initial = .{
            .DE = 0x1234,
        },
        .expected = .{
            .PC = 1,
            .DE = 0x1233,
        },
    });
}

test "DEC HL" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x2B,
        },
        .initial = .{
            .HL = 0x1234,
        },
        .expected = .{
            .PC = 1,
            .HL = 0x1233,
        },
    });
}

test "DEC SP" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x3B,
        },
        .initial = .{
            .SP = 0x1234,
        },
        .expected = .{
            .PC = 1,
            .SP = 0x1233,
        },
    });
}

test "INC B" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x04,
        },
        .initial = .{
            .BC = 0x0100,
        },
        .expected = .{
            .PC = 1,
            .BC = 0x0200,
        },
    });
}

test "INC C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x0C,
        },
        .initial = .{
            .BC = 0x0001,
        },
        .expected = .{
            .PC = 1,
            .BC = 0x0002,
        },
    });
}

test "INC D" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x14,
        },
        .initial = .{
            .DE = 0x0100,
        },
        .expected = .{
            .PC = 1,
            .DE = 0x0200,
        },
    });
}

test "INC E" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x1C,
        },
        .initial = .{
            .DE = 0x0001,
        },
        .expected = .{
            .PC = 1,
            .DE = 0x0002,
        },
    });
}

test "INC H" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x24,
        },
        .initial = .{
            .HL = 0x0100,
        },
        .expected = .{
            .PC = 1,
            .HL = 0x0200,
        },
    });
}

test "INC L" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x2C,
        },
        .initial = .{
            .HL = 0x0001,
        },
        .expected = .{
            .PC = 1,
            .HL = 0x0002,
        },
    });
}

test "INC (HL)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x34,
        },
        .initial = .{
            .HL = 0xF00D,
        },
        .expected = .{
            .PC = 1,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .initial = 0x56, .expected = 0x57 },
        },
    });
}

test "INC A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x3C,
        },
        .initial = .{
            .AF = 0x0100,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x0200,
        },
    });
}

test "DEC B" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x05,
        },
        .initial = .{
            .BC = 0x0200,
        },
        .expected = .{
            .PC = 1,
            .BC = 0x0100,
        },
    });
}

test "DEC C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x0D,
        },
        .initial = .{
            .BC = 0x0002,
        },
        .expected = .{
            .PC = 1,
            .BC = 0x0001,
        },
    });
}

test "DEC D" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x15,
        },
        .initial = .{
            .DE = 0x0200,
        },
        .expected = .{
            .PC = 1,
            .DE = 0x0100,
        },
    });
}

test "DEC E" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x1D,
        },
        .initial = .{
            .DE = 0x0002,
        },
        .expected = .{
            .PC = 1,
            .DE = 0x0001,
        },
    });
}

test "DEC H" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x25,
        },
        .initial = .{
            .HL = 0x0200,
        },
        .expected = .{
            .PC = 1,
            .HL = 0x0100,
        },
    });
}

test "DEC L" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x2D,
        },
        .initial = .{
            .HL = 0x0002,
        },
        .expected = .{
            .PC = 1,
            .HL = 0x0001,
        },
    });
}

test "DEC (HL)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x35,
        },
        .initial = .{
            .HL = 0xF00D,
        },
        .expected = .{
            .PC = 1,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .initial = 0x56, .expected = 0x55 },
        },
    });
}

test "DEC A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x3D,
        },
        .initial = .{
            .AF = 0x0200,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x0120,
        },
    });
}

test "LD B,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x06, 0x34,
        },
        .expected = .{
            .PC = 2,
            .BC = 0x3400,
        },
    });
}

test "LD C,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x0E, 0x34,
        },
        .expected = .{
            .PC = 2,
            .BC = 0x0034,
        },
    });
}

test "LD D,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x16, 0x34,
        },
        .expected = .{
            .PC = 2,
            .DE = 0x3400,
        },
    });
}

test "LD E,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x1E, 0x34,
        },
        .expected = .{
            .PC = 2,
            .DE = 0x0034,
        },
    });
}

test "LD H,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x26, 0x34,
        },
        .expected = .{
            .PC = 2,
            .HL = 0x3400,
        },
    });
}

test "LD L,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x2E, 0x34,
        },
        .expected = .{
            .PC = 2,
            .HL = 0x0034,
        },
    });
}

test "LD (HL),n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x36, 0x34,
        },
        .initial = .{
            .HL = 0xF00D,
        },
        .expected = .{
            .PC = 2,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .expected = 0x34 },
        },
    });
}

test "LD A,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x3E, 0x34,
        },
        .expected = .{
            .PC = 2,
            .AF = 0x3400,
        },
    });
}

test "RLCA" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x07,
        },
        .initial = .{
            .AF = 0b01100011_0001_0000,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b11000110_0000_0000,
        },
    });
}

test "RLA" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x17,
        },
        .initial = .{
            .AF = 0b01100011_0001_0000,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b11000111_0000_0000,
        },
    });
}

test "RRCA" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x0F,
        },
        .initial = .{
            .AF = 0b11000110_0001_0000,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b01100011_0000_0000,
        },
    });
}

test "RRA" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x1F,
        },
        .initial = .{
            .AF = 0b11000110_0001_0000,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b11100011_0000_0000,
        },
    });
}

test "DAA" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x27,
        },
        .initial = .{
            .AF = 42 << 8,
        },
        .expected = .{
            .PC = 1,
            .AF = (0x42 << 8),
        },
    });
}

test "CPL" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x2F,
        },
        .initial = .{
            .AF = 0b10101010_0000_0000,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b01010101_0110_0000,
        },
    });
}

test "SCF" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x37,
        },
        .initial = .{
            .AF = 0b10101010_0000_0000,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b10101010_0001_0000,
        },
    });
}

test "CCF" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x3F,
        },
        .initial = .{
            .AF = 0b10101010_0001_0000,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b10101010_0000_0000,
        },
    });
}

test "LD B,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x41,
        },
        .initial = .{
            .BC = 0x0042,
        },
        .expected = .{
            .PC = 1,
            .BC = 0x4242,
        },
    });
}

test "LD C,D" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x4a,
        },
        .initial = .{
            .DE = 0x4200,
        },
        .expected = .{
            .PC = 1,
            .BC = 0x0042,
        },
    });
}

test "LD D,E" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x53,
        },
        .initial = .{
            .DE = 0x0042,
        },
        .expected = .{
            .PC = 1,
            .DE = 0x4242,
        },
    });
}

test "LD E,H" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x5c,
        },
        .initial = .{
            .HL = 0x4200,
        },
        .expected = .{
            .PC = 1,
            .DE = 0x0042,
        },
    });
}

test "LD H,L" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x65,
        },
        .initial = .{
            .HL = 0x0042,
        },
        .expected = .{
            .PC = 1,
            .HL = 0x4242,
        },
    });
}

test "LD L,(HL)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x6E,
        },
        .initial = .{
            .HL = 0xF00D,
        },
        .expected = .{
            .PC = 1,
            .HL = 0xF056,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .initial = 0x56 },
        },
    });
}

test "LD (HL),A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x77,
        },
        .initial = .{
            .HL = 0xF00D,
            .AF = 0x4200,
        },
        .expected = .{
            .PC = 1,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .expected = 0x42 },
        },
    });
}

test "LD A,B" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x78,
        },
        .initial = .{
            .BC = 0x4200,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x4200,
        },
    });
}

test "HALT" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x76,
        },
        .expected = .{
            .PC = 1,
        },
        .state = .HALT,
    });
}

test "ADD A,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x81,
        },
        .initial = .{
            .AF = 0x4200 | 0b0001_0000,
            .BC = 0x0042,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x8400,
        },
    });
}

test "ADC A,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x89,
        },
        .initial = .{
            .AF = 0x4200 | 0b0001_0000,
            .BC = 0x0042,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x8500,
        },
    });
}

test "SUB A,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x91,
        },
        .initial = .{
            .AF = 0x4200 | 0b0001_0000,
            .BC = 0x0084,
        },
        .expected = .{
            .PC = 1,
            .AF = 0xBE00,
        },
    });
}

test "SBC A,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0x99,
        },
        .initial = .{
            .AF = 0x4200 | 0b0001_0000,
            .BC = 0x0084,
        },
        .expected = .{
            .PC = 1,
            .AF = 0xBF00,
        },
    });
}

test "AND A,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xA1,
        },
        .initial = .{
            .AF = 0b00111100_0000_0000,
            .BC = 0b00001111,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b00001100_0010_0000,
        },
    });
}

test "OR A,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xb1,
        },
        .initial = .{
            .AF = 0b00111100_0000_0000,
            .BC = 0b00001111,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b00111111_0000_0000,
        },
    });
}

test "XOR A,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xA9,
        },
        .initial = .{
            .AF = 0b00111100_0000_0000,
            .BC = 0b00001111,
        },
        .expected = .{
            .PC = 1,
            .AF = 0b00110011_0000_0000,
        },
    });
}

test "CP A,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xb9,
        },
        .initial = .{
            .AF = 0x4200,
            .BC = 0x0043,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x4200 | 0b0000_0000,
        },
    });
}

test "RET NZ" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xC0,
        },
        .initial = .{
            .AF = 0x0000 | 0b1000_0000,
            .SP = 0xF00D,
        },
        .expected = .{
            .SP = 0xF00D,
        },
    });
}

test "RET Z" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xC8,
        },
        .initial = .{
            .AF = 0x0000 | 0b1000_0000,
            .SP = 0xF00D,
        },
        .expected = .{
            .SP = 0xF00F,
            .PC = 0x1234,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00E, .initial = 0x12 },
            .{ .addr = 0xF00D, .initial = 0x34 },
        },
    });
}

test "RET NC" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xD0,
        },
        .initial = .{
            .AF = 0x0000 | 0b0001_0000,
            .SP = 0xF00D,
        },
        .expected = .{
            .SP = 0xF00D,
        },
    });
}

test "RET C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xD8,
        },
        .initial = .{
            .AF = 0x0000 | 0b0001_0000,
            .SP = 0xF00D,
        },
        .expected = .{
            .SP = 0xF00F,
            .PC = 0x1234,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00E, .initial = 0x12 },
            .{ .addr = 0xF00D, .initial = 0x34 },
        },
    });
}

test "RET" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xc9,
        },
        .initial = .{
            .SP = 0xF00D,
        },
        .expected = .{
            .SP = 0xF00F,
            .PC = 0x1234,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00E, .initial = 0x12 },
            .{ .addr = 0xF00D, .initial = 0x34 },
        },
    });
}

test "RETI" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xd9,
        },
        .initial = .{
            .SP = 0xF00D,
        },
        .expected = .{
            .SP = 0xF00F,
            .PC = 0x1234,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00E, .initial = 0x12 },
            .{ .addr = 0xF00D, .initial = 0x34 },
        },
        .IME = true,
    });
}

test "LD (nn),A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xEA, 0x0D, 0xF0,
        },
        .initial = .{
            .AF = 0x5600,
        },
        .expected = .{
            .PC = 3,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .expected = 0x56 },
        },
    });
}

test "LD A,(nn)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xFA, 0x0D, 0xF0,
        },
        .initial = .{
            .AF = 0x0000,
        },
        .expected = .{
            .PC = 3,
            .AF = 0x5600,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .initial = 0x56 },
        },
    });
}

test "LD (n),A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xE0, 0x0D,
        },
        .initial = .{
            .AF = 0x5600,
        },
        .expected = .{
            .PC = 2,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xFF0D, .expected = 0x56 },
        },
    });
}

test "LD A,(n)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xF0, 0x0D,
        },
        .initial = .{
            .AF = 0x0000,
        },
        .expected = .{
            .PC = 2,
            .AF = 0x5600,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xFF0D, .initial = 0x56 },
        },
    });
}

test "ADD SP,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xE8, 0x11,
        },
        .initial = .{
            .SP = 0x1223,
        },
        .expected = .{ .PC = 2, .SP = 0x1234 },
    });
}

test "LDHL SP,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xF8, 0x11,
        },
        .initial = .{
            .SP = 0x1223,
        },
        .expected = .{ .PC = 2, .HL = 0x1234 },
    });
}

test "POP BC" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xC1,
        },
        .initial = .{
            .SP = 0xF00D,
        },
        .expected = .{
            .PC = 1,
            .BC = 0x1234,
            .SP = 0xF00F,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00E, .initial = 0x12 },
            .{ .addr = 0xF00D, .initial = 0x34 },
        },
    });
}

test "POP AF" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xF1,
        },
        .initial = .{
            .SP = 0xF00D,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x1234,
            .SP = 0xF00F,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00E, .initial = 0x12 },
            .{ .addr = 0xF00D, .initial = 0x34 },
        },
    });
}

test "JP (HL)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xE9,
        },
        .initial = .{
            .HL = 0xF00D,
        },
        .expected = .{
            .PC = 0x1234,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00D, .initial = 0x34 },
            .{ .addr = 0xF00E, .initial = 0x12 },
        },
    });
}

test "LD SP,HL" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xF9,
        },
        .initial = .{
            .HL = 0x1234,
        },
        .expected = .{
            .PC = 1,
            .SP = 0x1234,
        },
    });
}

test "JP NZ" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xC2, 0x34, 0x12,
        },
        .initial = .{
            .AF = 0x0000 | 0b1000_0000,
        },
        .expected = .{
            .PC = 3,
        },
    });
}

test "JP Z" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCA, 0x34, 0x12,
        },
        .initial = .{
            .AF = 0x0000 | 0b1000_0000,
        },
        .expected = .{
            .PC = 0x1234,
        },
    });
}

test "JP NC" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xD2, 0x34, 0x12,
        },
        .initial = .{
            .AF = 0x0000 | 0b0001_0000,
        },
        .expected = .{
            .PC = 3,
        },
    });
}

test "JP C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xDA, 0x34, 0x12,
        },
        .initial = .{
            .AF = 0x0000 | 0b0001_0000,
        },
        .expected = .{
            .PC = 0x1234,
        },
    });
}

test "LD (C),A" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xE2,
        },
        .initial = .{
            .AF = 0x5600,
            .BC = 0x000D,
        },
        .expected = .{
            .PC = 1,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xFF0D, .expected = 0x56 },
        },
    });
}

test "LD A,(C)" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xF2,
        },
        .initial = .{
            .AF = 0x0000,
            .BC = 0x000D,
        },
        .expected = .{
            .PC = 1,
            .AF = 0x5600,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xFF0D, .initial = 0x56 },
        },
    });
}

test "DI" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xF3,
        },
        .expected = .{
            .PC = 1,
        },
        .IME = false,
    });
}

test "EI" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xFB,
        },
        .expected = .{
            .PC = 1,
        },
        .IME = true,
    });
}

test "CALL NZ" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xC4, 0x34, 0x12,
        },
        .initial = .{
            .AF = 0x0000 | 0b1000_0000,
            .SP = 0xF00D,
        },
        .expected = .{
            .PC = 3,
            .SP = 0xF00D,
        },
    });
}

test "CALL Z" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCC, 0x34, 0x12,
        },
        .initial = .{
            .AF = 0x0000 | 0b1000_0000,
            .SP = 0xF00D,
        },
        .expected = .{
            .PC = 0x1234,
            .SP = 0xF00B,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00C, .initial = 0x12 },
            .{ .addr = 0xF00B, .initial = 0x34 },
        },
    });
}

test "CALL" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCD, 0x34, 0x12,
        },
        .initial = .{
            .SP = 0xF00D,
        },
        .expected = .{
            .PC = 0x1234,
            .SP = 0xF00B,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00C, .initial = 0x12 },
            .{ .addr = 0xF00B, .initial = 0x34 },
        },
    });
}

test "PUSH BC" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xC5,
        },
        .initial = .{
            .BC = 0x1234,
            .SP = 0xF00D,
        },
        .expected = .{
            .PC = 1,
            .SP = 0xF00B,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00C, .initial = 0x12 },
            .{ .addr = 0xF00B, .initial = 0x34 },
        },
    });
}

test "PUSH AF" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xF5,
        },
        .initial = .{
            .AF = 0x1234,
            .SP = 0xF00D,
        },
        .expected = .{
            .PC = 1,
            .SP = 0xF00B,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00C, .initial = 0x12 },
            .{ .addr = 0xF00B, .initial = 0x34 },
        },
    });
}

test "ADC A,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCE, 0x12,
        },
        .initial = .{
            .AF = 0x5600 | 0b0001_0000,
        },
        .expected = .{
            .PC = 2,
            .AF = 0x6900,
        },
    });
}

test "SBC A,n" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xDE, 0x12,
        },
        .initial = .{
            .AF = 0x5600 | 0b0001_0000,
        },
        .expected = .{
            .PC = 2,
            .AF = 0x4500 | 0b0011_0000,
        },
    });
}

test "RST $38" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xff,
        },
        .initial = .{
            .SP = 0xF00D,
        },
        .expected = .{
            .PC = 0x0038,
            .SP = 0xF00B,
        },
        .memory = &[_]MemorySpec{
            .{ .addr = 0xF00C, .expected = 0x00 },
            .{ .addr = 0xF00B, .expected = 0x01 },
        },
    });
}

test "RLC C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x01,
        },
        .initial = .{
            .AF = 0b0001_0000,
            .BC = 0b01100011,
        },
        .expected = .{
            .PC = 2,
            .AF = 0b0000_0000,
            .BC = 0b11000110,
        },
    });
}

test "RL C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x11,
        },
        .initial = .{
            .AF = 0b0001_0000,
            .BC = 0b01100011,
        },
        .expected = .{
            .PC = 2,
            .AF = 0b0000_0000,
            .BC = 0b11000111,
        },
    });
}

test "RRC C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x09,
        },
        .initial = .{
            .AF = 0b0001_0000,
            .BC = 0b11000110,
        },
        .expected = .{
            .PC = 2,
            .AF = 0b0000_0000,
            .BC = 0b01100011,
        },
    });
}

test "RR C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x19,
        },
        .initial = .{
            .AF = 0b0001_0000,
            .BC = 0b11000110,
        },
        .expected = .{
            .PC = 2,
            .AF = 0b0000_0000,
            .BC = 0b11100011,
        },
    });
}

test "SLA C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x21,
        },
        .initial = .{
            .AF = 0b0001_0000,
            .BC = 0b01110000,
        },
        .expected = .{
            .PC = 2,
            .AF = 0b0000_0000,
            .BC = 0b11100000,
        },
    });
}

test "SRA C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x29,
        },
        .initial = .{
            .AF = 0b0000_0000,
            .BC = 0b11110001,
        },
        .expected = .{
            .PC = 2,
            .AF = 0b0001_0000,
            .BC = 0b11111000,
        },
    });
}

test "SWAP C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x31,
        },
        .initial = .{
            .BC = 0x42,
        },
        .expected = .{
            .PC = 2,
            .BC = 0x24,
        },
    });
}

test "SRL C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x39,
        },
        .initial = .{
            .AF = 0b0000_0000,
            .BC = 0b11110001,
        },
        .expected = .{
            .PC = 2,
            .AF = 0b0001_0000,
            .BC = 0b01111000,
        },
    });
}

test "BIT 3,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x59,
        },
        .initial = .{
            .BC = 0b11110111,
        },
        .expected = .{
            .PC = 2,
            .AF = 0b1010_0000,
        },
    });
}

test "SET 3,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0xd9,
        },
        .initial = .{
            .BC = 0b00000000,
        },
        .expected = .{
            .PC = 2,
            .BC = 0b00001000,
        },
    });
}

test "RES 3,C" {
    try opcodeTest(.{
        .input = &[_]u8{
            0xCB, 0x99,
        },
        .initial = .{
            .BC = 0b11111111,
        },
        .expected = .{
            .PC = 2,
            .BC = 0b11110111,
        },
    });
}
