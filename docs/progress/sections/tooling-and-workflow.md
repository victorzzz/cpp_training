# Section Progress: Tooling and Workflow

## Goals

- Stable one-key build and debug in VS Code on Windows
- Compile C++20 with MSVC
- Fast edit-build-run loop

## Checklist

- [x] Add VS Code tasks for build and run
- [x] Add debug launch config
- [x] Add robust MSVC environment bootstrap script
- [x] Validate build on first C++ source file
- [ ] Validate breakpoint debugging

## Session Log

- 2026-03-04: Initial configuration files created.
- 2026-03-04: Built and ran `src/sanity_check.cpp` successfully with MSVC C++20.

## Common Issues

- `cl` not found: run through build script, which initializes `VsDevCmd.bat`.
- Wrong toolset: verify Visual Studio installation includes C++ workload.
