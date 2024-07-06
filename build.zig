const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "main",
        .target = target,
        .optimize = optimize,
    });
    exe.linkSystemLibrary("c");
    exe.linkSystemLibrary("raylib");

    const flags = .{ "-Wall", "-Wextra", "-lraylib" };
    exe.addCSourceFile(.{
        .file = .{ .path = "src/main.c" },
        .flags = &flags,
    });

    exe.addCSourceFile(.{
        .file = .{ .path = "src/block.c" },
        .flags = &flags,
    });

    exe.addCSourceFile(.{
        .file = .{ .path = "src/queue.c" },
        .flags = &flags,
    });

    exe.addCSourceFile(.{
        .file = .{ .path = "src/sorters.c" },
        .flags = &flags,
    });

    b.installArtifact(exe);

    const run_exe = b.addRunArtifact(exe);

    const run_step = b.step("run", "Run the application");
    run_step.dependOn(&run_exe.step);
    b.default_step.dependOn(&exe.step);
}
