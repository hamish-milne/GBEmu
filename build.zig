const std = @import("std");
const builtin = @import("builtin");

// Although this function looks imperative, note that its job is to
// declaratively construct a build graph that will be executed by an external
// runner.
pub fn build(b: *std.Build) !void {

    // Standard target options allows the person running `zig build` to choose
    // what target to build for. Here we do not override the defaults, which
    // means any target is allowed, and the default is native. Other options
    // for restricting supported target set are available.
    const target = b.standardTargetOptions(.{});

    // Standard optimization options allow the person running `zig build` to select
    // between Debug, ReleaseSafe, ReleaseFast, and ReleaseSmall. Here we do not
    // set a preferred release mode, allowing the user to decide how to optimize.
    const optimize = b.standardOptimizeOption(.{});

    const targetTrip = blk: {
        var target2 = target;
        target2.cpu_model = .baseline;
        if (target.isWindows()) {
            target2.abi = .msvc;
        }
        break :blk target2;
    };

    const options = .{
        .name = "GBEmu",
        // In this case the main source file is merely a path, however, in more
        // complicated build scripts, this could be a generated file.
        .root_source_file = .{ .path = "src/main.zig" },
        .optimize = optimize,
        .link_libc = true,
        .target = targetTrip,
    };

    const glad = b.addObject(.{
        .name = "glad",
        .optimize = optimize,
        .link_libc = true,
        .target = targetTrip,
    });
    // https://github.com/ziglang/zig/issues/19423
    glad.addCSourceFile(.{
        .file = .{ .path = "src/gl.c" },
        .flags = &[_][]const u8{ "-std=c99", "-pedantic", "-Werror", "-Wall", "-DGLAD_API_CALL=" },
    });
    glad.addIncludePath(.{ .path = "include" });

    const exe = b.addExecutable(options);

    // This declares intent for the executable to be installed into the
    // standard location when the user invokes the "install" step (the default
    // step when running `zig build`).
    b.installArtifact(exe);

    // This *creates* a Run step in the build graph, to be executed when another
    // step is evaluated that depends on it. The next line below will establish
    // such a dependency.
    const run_cmd = b.addRunArtifact(exe);

    // By making the run step depend on the install step, it will be run from the
    // installation directory rather than directly from within the cache directory.
    // This is not necessary, however, if the application depends on other installed
    // files, this ensures they will be present and in the expected location.
    run_cmd.step.dependOn(b.getInstallStep());

    // This allows the user to pass arguments to the application in the build
    // command itself, like this: `zig build run -- arg1 arg2 etc`
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    // This creates a build step. It will be visible in the `zig build --help` menu,
    // and can be selected like this: `zig build run`
    // This will evaluate the `run` step rather than the default, which is "install".
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);

    // Creates a step for unit testing. This only builds the test executable
    // but does not run it.
    const unit_tests = b.addTest(blk: {
        var opts: std.build.TestOptions = options;
        opts.name = "test";
        break :blk opts;
    });
    b.installArtifact(unit_tests);

    const run_unit_tests = b.addRunArtifact(unit_tests);

    // Similar to creating the run step earlier, this exposes a `test` step to
    // the `zig build --help` menu, providing a way for the user to request
    // running the unit tests.
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_unit_tests.step);

    inline for (.{ exe, unit_tests }) |obj| {
        obj.addObject(glad);
        if (target.isWindows()) {
            inline for (.{ "User32", "Shell32", "Ole32", "Gdi32" }) |lib| {
                obj.linkSystemLibrary(lib);
            }
        }

        inline for (.{ "glfw3", "soundio" }) |lib| {
            obj.addObjectFile(.{ .path = try std.mem.concat(b.allocator, u8, &[_][]const u8{ "deps/lib/" ++ lib, target.staticLibSuffix() }) });
        }
        obj.addIncludePath(.{ .path = "deps/include" });
        obj.addIncludePath(.{ .path = "include" });
    }
}
