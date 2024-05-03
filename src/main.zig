const std = @import("std");
const C = @import("C.zig");
const audio = @import("audio.zig");
const memory = @import("memory.zig");
const cpu = @import("cpu.zig");
const graphics = @import("graphics.zig");
const GameState = @import("gameState.zig").GameState;

//
// pub const GameState = struct {
//     Memory: memory.Memory,
//     CPU: cpu.CPU,
//     Screen: graphics.Screen,
//     Audio: audio.Audio,
// };

// zig fmt: off
// const TestROM = [_]u8 {
//     0x00, 0x00, 0x00, 0x00,
//     0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
//     0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
//     0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
//     'T', 'E', 'S', 'T', ' ', 'R', 'O', 'M', ' ', 'N', 'O', 'T', ' ', 'V', 'A', 'L',
//     0, 0, 0, 0, 0, 0, 0, 0, 0
// };
// zig fmt: on

// comptime {
//     if (TestROM.len != 0x4d) {
//         @compileLog(TestROM.len);
//         @compileError("TestROM must be 0x4d bytes long");
//     }
// }

// fn complement(rom: []const u8) u8 {
//     var sum: u8 = 0x19;
//     for (rom) |byte| {
//         sum +%= byte;
//     }
//     return -%sum;
// }

// const FullROM = BootROM ++ TestROM ++ [_]u8{complement(TestROM[0x34..])};

pub fn main() !void {
    if (C.glfwInit() == 0) return error.NoGLFW;
    const window = C.glfwCreateWindow(160, 144, "Gameboy", null, null) orelse return error.OutOfMemory;
    const window2 = C.glfwCreateWindow(16 * 8, 24 * 8, "VRAM", null, null) orelse return error.OutOfMemory;
    C.glfwMakeContextCurrent(window);
    C.glfwSwapInterval(1);
    defer C.glfwTerminate();

    var audioState: audio.State = .{};
    try audioState.init();
    defer audioState.deinit();

    var state: GameState = undefined;
    state.init(&audioState.Buffer, @embedFile("09-op r,r.gb"));

    var vramBuf: [16 * 24 * 8 * 8]u8 = undefined;

    // @memset(memory.asBytes(GameState, &state), 0);
    // state.Memory.ROM = FullROM;
    // state.CPU.PC = 0x0;
    // var frameCount: u32 = 0;
    // const stdout = std.io.getStdOut().writer();
    // while (state.CPU.PC < 0x100) {
    //     // std.debug.print("{x},{x},{x},{x},{x}  ", .{ state.CPU.PC, state.CPU.R.u8.A, state.CPU.R.u8.C, state.CPU.R.u16.HL, state.CPU.R.u16.DE });
    //     state.CPU.mainLoop(&state.Memory, &state.Screen);
    //     frameCount += 1;
    //     // for (state.Screen) |row| {
    //     //     for (row) |pixel| {
    //     //         try stdout.writeByte(switch (pixel >> 6) {
    //     //             0 => ' ',
    //     //             1 => '.',
    //     //             2 => 'x',
    //     //             3 => '#',
    //     //             else => '?',
    //     //         });
    //     //     }
    //     //     try stdout.writeByte('\n');
    //     // }
    // }
    // std.debug.print("success! total frames = {}", .{frameCount});

    while (C.glfwWindowShouldClose(window) == 0) {
        C.glfwMakeContextCurrent(window);
        // C.glClearColor(1.0, 1.0, 1.0, 0.0);
        // C.glClear(C.GL_COLOR_BUFFER_BIT);

        C.glPixelMapfv(C.GL_PIXEL_MAP_I_TO_A, 4, &[_]C.GLfloat{ 1.0, 1.0, 1.0, 1.0 });
        inline for (.{ C.GL_PIXEL_MAP_I_TO_R, C.GL_PIXEL_MAP_I_TO_G, C.GL_PIXEL_MAP_I_TO_B }) |map| {
            C.glPixelMapfv(map, 4, &[_]C.GLfloat{ 1.0, 0.67, 0.33, 0 });
        }
        C.glDrawPixels(state.Screen[0].len, state.Screen.len, C.GL_COLOR_INDEX, C.GL_UNSIGNED_BYTE, &state.Screen);
        C.glfwSwapBuffers(window);
        C.glfwPollEvents();

        if (state.AudioBuffer.Count < audio.AudioRingBuffer.Length / 2) {
            state.mainLoop();
        }

        C.glfwMakeContextCurrent(window2);
        for (state.Memory.VRAM.Data, 0..) |tile, tileIdx| {
            for (tile, 0..) |tileRow, rowIdx| {
                const y = (tileIdx / 16) * 8 + rowIdx;
                for (0..8) |col| {
                    const x = tileIdx % 16 * 8 + col;
                    const tileCol: u4 = @intCast(col);
                    const rawColor = ((tileRow >> (7 - tileCol)) & 1) | (((tileRow >> (15 - tileCol)) & 1) << 1);
                    vramBuf[y * 16 * 8 + x] = @truncate(rawColor);
                }
            }
        }
        C.glPixelMapfv(C.GL_PIXEL_MAP_I_TO_A, 4, &[_]C.GLfloat{ 1.0, 1.0, 1.0, 1.0 });
        inline for (.{ C.GL_PIXEL_MAP_I_TO_R, C.GL_PIXEL_MAP_I_TO_G, C.GL_PIXEL_MAP_I_TO_B }) |map| {
            C.glPixelMapfv(map, 4, &[_]C.GLfloat{ 1.0, 0.67, 0.33, 0 });
        }
        C.glDrawPixels(16 * 8, 24 * 8, C.GL_COLOR_INDEX, C.GL_UNSIGNED_BYTE, &vramBuf);
        C.glfwSwapBuffers(window2);
    }
}

test {
    std.testing.refAllDecls(@This());
}
