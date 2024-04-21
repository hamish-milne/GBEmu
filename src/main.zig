const std = @import("std");
const C = @import("C.zig");
const audio = @import("audio.zig");
const memory = @import("memory.zig");
const cpu = @import("cpu.zig");
const graphics = @import("graphics.zig");

pub const GameState = struct {
    Memory: memory.Memory,
    CPU: cpu.CPU,
    Screen: graphics.Screen,
};

const BootROM = @embedFile("DMG_ROM.bin");

var audioBuffer: audio.AudioRingBuffer = .{};

pub fn main() !void {
    // if (C.glfwInit() == 0) return error.NoGLFW;
    // const window = C.glfwCreateWindow(160, 144, "Gameboy", null, null) orelse return error.OutOfMemory;
    // C.glfwMakeContextCurrent(window);
    // defer C.glfwTerminate();

    var audioState: audio.State = undefined;
    try audioState.init(&audioBuffer);
    defer audioState.deinit();

    var state: GameState = undefined;
    @memset(memory.asBytes(GameState, &state), 0);
    state.Memory.ROM = BootROM;
    state.CPU.PC = 0x100;
    while (true) {
        state.CPU.mainLoop(&state.Memory, &state.Screen);
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
