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

## Coding Tasks (Practical Drills)

- Build-run loop drill:
 	- Create `src/day1_loop.cpp` with 3 small functions and one deliberate compile error.
 	- Fix to green build in under 5 minutes.
 	- Target: one-key build + one-key run workflow confidence.
- Debug drill in VS Code:
 	- Add breakpoint inside loop; inspect variables and call stack.
 	- Step into and step over at least once each.
 	- Target: validate breakpoint debugging checklist item.
- Warning cleanup drill:
 	- Introduce one signed/unsigned comparison warning.
 	- Fix warning without suppressing diagnostics.
 	- Target: zero warnings on `/W4` for the drill file.

## Session Log

- 2026-03-04: Initial configuration files created.
- 2026-03-04: Built and ran `src/sanity_check.cpp` successfully with MSVC C++20.
- 2026-03-04 (Day 1, Block 1, 30 min): Re-ran build/run workflow; fixed Windows task quoting by calling `scripts/build_active_msvc.bat` directly in `.vscode/tasks.json`.
- 2026-03-04 (Day 1, Block 1): Validation outcome: active file build and run task chain executes with corrected task command.

## Common Issues

- `cl` not found: run through build script, which initializes `VsDevCmd.bat`.
- Wrong toolset: verify Visual Studio installation includes C++ workload.
- Nested `cmd /c` in VS Code shell task can break quoting on Windows; prefer direct batch invocation with file path as a separate argument.
