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
    A: u8,
    C: bool,
    H: bool,
    N: bool,
    Z: bool,
    R: extern union {
        u8: extern struct {
            C: u8 align(1),
            B: u8 align(1),
            E: u8 align(1),
            D: u8 align(1),
            L: u8 align(1),
            H: u8 align(1),
        },
        u16: extern struct {
            BC: u16 align(2),
            DE: u16 align(2),
            HL: u16 align(2),
        },
    },
    IME: bool,

    mem: *Memory,

    const AF = packed struct {
        _: u4,
        C: bool,
        H: bool,
        N: bool,
        Z: bool,
        A: u8,
    };

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
            .In => if (self.C) 1 else 0,
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
        const resultH = (a1 & 0xF) + (b1 & 0xF) + c1;
        const c4 = resultH & 0b10000 != 0;
        const c9 = result & 0b100000000 != 0;
        self.Z = value == 0;
        self.N = op == .Sub;
        self.H = switch (op) {
            .Add => c4,
            .Sub => !c4,
        };
        if (carry != .None) {
            self.C = switch (op) {
                .Add => c9,
                .Sub => !c9,
            };
        }
        return value;
    }

    fn add16s8(self: *CPU, a: u16, b: u8) u16 {
        const bi = @as(i8, @bitCast(b));
        // sign-extend b
        const b16: u16 = @bitCast(@as(i16, bi));
        const result = @as(u17, a) + b16;
        const value: u16 = @truncate(result);
        self.Z = false;
        self.N = false;
        self.H = (a & 0xF) + (b & 0xF) > 0xF;
        self.C = (a & 0xFF) + (b & 0xFF) > 0xFF;
        return value;
    }

    fn flags(self: *CPU, value: u8, h: bool, c: bool) u8 {
        self.Z = value == 0;
        self.N = false;
        self.H = h;
        self.C = c;
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
            7 => self.A,
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
            7 => self.A = value,
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
            2, 3 => if (self.C) 1 else 0,
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
            0 => !self.Z,
            1 => self.Z,
            2 => !self.C,
            3 => self.C
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
                            const a: u17 = self.R.u16.HL;
                            const b: u17 = regPtr.*;
                            const result = a + b;
                            const value: u16 = @truncate(result);
                            self.N = false;
                            self.H = (a & 0xFFF) + (b & 0xFFF) > 0xFFF;
                            self.C = result > 0xFFFF;
                            self.R.u16.HL = value;
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
                            self.write(regPtr.a.*, self.A);
                        } else {
                            self.A = self.read(regPtr.a.*);
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
                            self.A = self.rotate(@intCast(block2), self.A);
                            self.Z = false;
                            break :blk 1;
                        },
                        4 => blk: {
                            // DAA
                            const a = self.A;
                            const n = self.N;
                            const d0: u8 = if (self.H or (!n and (a & 0xF) > 9)) 0x6 else 0;
                            const d1: u8 = if (self.C or (!n and a > 0x99)) 0x60 else 0;
                            const d = d0 + d1;
                            const result = if (n) a -% d else a +% d;
                            self.A = result;
                            self.Z = result == 0;
                            self.C = d1 != 0;
                            self.H = false;
                            break :blk 1;
                        },
                        5 => blk: {
                            // CPL
                            self.A = ~self.A;
                            self.N = true;
                            self.H = true;
                            break :blk 1;
                        },
                        6 => blk: {
                            // SCF
                            self.N = false;
                            self.H = false;
                            self.C = true;
                            break :blk 1;
                        },
                        7 => blk: {
                            // CCF
                            self.N = false;
                            self.H = false;
                            self.C = !self.C;
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
                    0 => self.A = self.add(self.A, value, .Add, .Set),
                    1 => self.A = self.add(self.A, value, .Add, .In),
                    2 => self.A = self.add(self.A, value, .Sub, .Set),
                    3 => self.A = self.add(self.A, value, .Sub, .In),
                    4 => self.A = self.flags(self.A & value, true, false),
                    5 => self.A = self.flags(self.A ^ value, false, false),
                    6 => self.A = self.flags(self.A | value, false, false),
                    7 => _ = self.add(self.A, value, .Sub, .Set),
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
                            self.write(0xFF00 + @as(u16, self.readPC()), self.A);
                            break :blk 3;
                        },
                        // LD A,(n)
                        6 => blk: {
                            self.A = self.read(0xFF00 + @as(u16, self.readPC()));
                            break :blk 3;
                        },
                        // ADD SP,n
                        5 => blk: {
                            self.SP = self.add16s8(self.SP, self.readPC());
                            break :blk 4;
                        },
                        // LDHL SP,n
                        7 => blk: {
                            self.R.u16.HL = self.add16s8(self.SP, self.readPC());
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
                                3 => {
                                    const af: AF = @bitCast(value);
                                    self.A = af.A;
                                    self.C = af.C;
                                    self.H = af.H;
                                    self.N = af.N;
                                    self.Z = af.Z;
                                },
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
                            self.write(0xFF00 + @as(u16, self.R.u8.C), self.A);
                            break :blk 2;
                        },
                        // LD (nn),A
                        5 => blk: {
                            self.write(self.readPC16(), self.A);
                            break :blk 4;
                        },
                        // LD A,(C)
                        6 => blk: {
                            self.A = self.read(0xFF00 + @as(u16, self.R.u8.C));
                            break :blk 2;
                        },
                        // LD A,(nn)
                        7 => blk: {
                            self.A = self.read(self.readPC16());
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
                            3 => @bitCast(AF {
                                .A = self.A,
                                ._ = 0,
                                .C = self.C,
                                .H = self.H,
                                .N = self.N,
                                .Z = self.Z,
                            }),
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
                self.Z = (value & bit) == 0;
                self.N = false;
                self.H = true;
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
        const IF: u8 = @bitCast(IOPorts.IF);
        const IE: u8 = self.mem.HiRAM[0x7F];
        const interruptsN = IF & IE & 0b11111;
        if (interruptsN != 0) {
            self.RunState = .Running;
            if (self.IME) {
                self.IME = false;
                self.push(self.PC);
                inline for(0..5) |i| {
                    const bit = @as(u8, 1) << i;
                    if (interruptsN & bit != 0) {
                        IOPorts.IF = @bitCast(IF & ~bit);
                        self.PC = 0x40 + (i << 3);
                        return true;
                    }
                }
                unreachable;
            }
        }
        return false;
    }

};
