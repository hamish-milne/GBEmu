const std = @import("std");
const C = @import("C.zig");
const audio = @import("audio.zig");
const memory = @import("memory.zig");
const cpu = @import("cpu.zig");
const graphics = @import("graphics.zig");
const GameState = @import("gameState.zig").GameState;

pub fn main() !void {
    if (C.glfwInit() == 0) return error.NoGLFW;
    defer C.glfwTerminate();
    const window = C.glfwCreateWindow(graphics.Width, graphics.Height, "Gameboy", null, null) orelse return error.OutOfMemory;

    C.glfwMakeContextCurrent(window);
    C.glfwSwapInterval(0);
    _ = C.gladLoadGL(C.glfwGetProcAddress);

    var audioState: audio.State = .{};
    try audioState.init();
    defer audioState.deinit();

    var state: GameState = undefined;
    state.init(&audioState.Buffer, @embedFile("bgbtest.gb"));

    C.glPixelTransferi(C.GL_MAP_COLOR, C.GL_TRUE);
    C.glPixelMapfv(C.GL_PIXEL_MAP_I_TO_A, 4, &[_]C.GLfloat{ 1.0, 1.0, 1.0, 1.0 });
    inline for (.{ C.GL_PIXEL_MAP_I_TO_R, C.GL_PIXEL_MAP_I_TO_G, C.GL_PIXEL_MAP_I_TO_B }) |map| {
        C.glPixelMapfv(map, 4, &[_]C.GLfloat{ 1.0, 0.67, 0.33, 0 });
    }

    // create screen texture
    var texture: C.GLuint = 0;
    C.glGenTextures(1, &texture);
    C.glBindTexture(C.GL_TEXTURE_2D, texture);
    C.glTexParameteri(C.GL_TEXTURE_2D, C.GL_TEXTURE_MIN_FILTER, C.GL_NEAREST);
    C.glTexParameteri(C.GL_TEXTURE_2D, C.GL_TEXTURE_MAG_FILTER, C.GL_NEAREST);
    C.glTexParameteri(C.GL_TEXTURE_2D, C.GL_TEXTURE_WRAP_S, C.GL_CLAMP_TO_EDGE);
    C.glTexParameteri(C.GL_TEXTURE_2D, C.GL_TEXTURE_WRAP_T, C.GL_CLAMP_TO_EDGE);
    C.glTexImage2D(C.GL_TEXTURE_2D, 0, 1, graphics.Width, graphics.Height, 0, C.GL_COLOR_INDEX, C.GL_UNSIGNED_BYTE, &state.Screen);

    // create FBO
    var fbo: C.GLuint = 0;
    C.glGenFramebuffers(1, &fbo);
    C.glBindFramebuffer(C.GL_READ_FRAMEBUFFER, fbo);
    C.glFramebufferTexture2D(C.GL_READ_FRAMEBUFFER, C.GL_COLOR_ATTACHMENT0, C.GL_TEXTURE_2D, texture, 0);

    C.glBindFramebuffer(C.GL_DRAW_FRAMEBUFFER, 0);

    var time = C.glfwGetTime();
    var frameCount: u64 = 0;

    // const stdout = std.io.getStdOut();
    // _ = try stdout.write("\x1b[?25l\x1b[0m\x1b[2J");

    while (C.glfwWindowShouldClose(window) == 0) {
        const newTime = C.glfwGetTime();
        if (newTime - time >= 1.0) {
            time = newTime;
            // std.debug.print("FPS: {}\n", .{frameCount});
            frameCount = 0;
        }

        if (state.AudioBuffer.Count < audio.AudioRingBuffer.Length / 2) {
            frameCount += 1;
            state.mainLoop();

            C.glTexSubImage2D(C.GL_TEXTURE_2D, 0, 0, 0, graphics.Width, graphics.Height, C.GL_COLOR_INDEX, C.GL_UNSIGNED_BYTE, &state.Screen);
            C.glBlitFramebuffer(0, 0, graphics.Width, graphics.Height, 0, 0, graphics.Width, graphics.Height, C.GL_COLOR_BUFFER_BIT, C.GL_NEAREST);

            C.glfwSwapBuffers(window);
            C.glfwPollEvents();

            // termidx = 0;
            // append("\x1b[H");
            // for (0..graphics.Height / 2) |y| {
            //     for (0..graphics.Width) |x| {
            //         append("\x1b[38;5;");
            //         append(switch (state.Screen[graphics.Height - (y * 2) - 1][x]) {
            //             else => "255",
            //             1 => "248",
            //             2 => "238",
            //             3 => "232",
            //         });
            //         append("m\x1b[48;5;");
            //         append(switch (state.Screen[graphics.Height - (y * 2) - 2][x]) {
            //             else => "255",
            //             1 => "248",
            //             2 => "238",
            //             3 => "232",
            //         });
            //         append("m\u{2580}");
            //     }
            //     append("\x1b[0m\n");
            // }
            // _ = try stdout.write(termbuf[0..termidx]);
        } else {
            std.time.sleep(1_000_000);
        }
    }
}

var termbuf: [512 * 1024]u8 = undefined;
var termidx: usize = 0;

fn append(str: []const u8) void {
    for (str, 0..) |c, i| {
        termbuf[termidx + i] = c;
    }
    termidx += str.len;
}

fn modify(str: []const u8, idx: usize) void {
    for (str, 0..) |c, i| {
        termbuf[idx + i] = c;
    }
}

test {
    std.testing.refAllDecls(@This());
}
