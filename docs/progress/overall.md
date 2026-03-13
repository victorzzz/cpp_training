# Overall Progress

## Current Status

- Interview date target: in 10 days
- Plan duration: 8 active preparation days
- Total planned time: 28 hours
- Completed time: 3.0/28 hours

## Day Tracker

- [x] Day 1 (2h): Setup + Refresh
- [ ] Day 2 (2h): Core Memory Model
- [ ] Day 3 (2h): STL + Ranges
- [ ] Day 4 (2h): Templates + Concepts
- [ ] Day 5 (2h): Concurrency + Error Handling
- [ ] Day 6 (6h): Problem Marathon I
- [ ] Day 7 (6h): Problem Marathon II
- [ ] Day 8 (6h): Final Simulation

## Health Check (update each session)

- C++20 language confidence: Low
- STL/ranges confidence: Low
- Problem solving speed: Low
- Verbal explanation clarity: Medium

## Notes

- Start every session by opening `docs/interview-plan.md` and this file.
- Log concrete mistakes and fixes in section files.
- 2026-03-12 Day 5 session started (strict coaching mode): moved to concurrency + error handling with fail-first `std::thread` counter drill in `src/concurrency/counter_race_drill.cpp`.
- 2026-03-12 Day 5 drill complete: implemented mutex-protected shared counter with `std::thread`, `std::lock_guard`, negative-input validation, and join safety under MSVC C++20; harness passed 5/5 and the intentional race demo observed lost updates.
- 2026-03-12 Day 5 async drill started: added fail-first `std::async` parallel sum scaffold in `src/concurrency/async_parallel_sum_drill.cpp` with explicit `std::launch::async` requirement and `0/5` passing baseline.
- 2026-03-12 Day 5 async drill continued: added `parallel_sum_async_nice` as a cleaner reference implementation using balanced contiguous chunking and `future.get()` aggregation; combined harness passed 16/16 under MSVC C++20.
- 2026-03-12 Day 5 error-handling drill started: added fail-first timeout parser scaffold in `src/error_handling/timeout_parser_drill.cpp` using `std::optional`, `std::from_chars`, and a throwing wrapper; baseline is 6/11 under MSVC C++20.
- 2026-03-04 Day 1 Block 1 complete (30 min): Build/run workflow validated, task quoting issue found and fixed in `.vscode/tasks.json`; rerun succeeded.
- 2026-03-04 Correction: Blocks 2-3 were logged ahead of live practice; reverted to pending so session reflects only completed work.
- 2026-03-04 Day 1 Block 2 complete (30 min, live): Value categories, `std::move` behavior, and Rule-of-0 policy selection practiced with corrections.
- 2026-03-04 Day 1 Block 3 complete (30 min, live): Container choice drill completed with strict complexity + memory behavior framing (`unordered_set` vs `set`).
- 2026-03-04 Day 1 status: in progress (3/4 blocks completed).
- 2026-03-06 Day 1 Block 4 complete (30 min, live): Solved Two Sum and Longest Substring; corrected hash-map complexity phrasing and fixed stale-map bug by switching to one-pass sliding window.
- 2026-03-07 Additional practice block complete (60 min): Daily Temperatures and Rotated Sorted Array Search implemented with test-driven validation and boundary-case fixes.
- 2026-03-07 Session resumed (strict coaching mode): advancing to Course Schedule (topological sort, target O(V+E)) with code-first tests.
- 2026-03-07 Course Schedule completed (Kahn BFS topological sort): validated DAG/cycle criterion with O(V+E) implementation and passing scaffold tests.
- 2026-03-08 DP drill complete: House Robber solved with memoization and reviewed against rolling DP optimization target.
- 2026-03-08 DP drill complete: House Robber II (circular constraint) solved with split-range rolling DP and boundary-case fix for n<=2.
- 2026-03-08 DP drill complete: Coin Change solved with bottom-up DP (`O(amount * coins)`, `O(amount)` space) after fail-first scaffold.
- 2026-03-12 STL syntax session: Top-K frequent words drill implemented with `unordered_map` + comparator ordering (count desc, word asc); compared `sort` vs `partial_sort` and diagnosed MSVC compile error caused by sorting `std::pair<const std::string, int>` map value type.
- 2026-03-12 STL syntax session continued: moved to concepts-gated `sum_range` drill with code-first tests and compile-time constraints (`input_range` + arithmetic value type). Scaffold is fail-first by design (1/4 passing before implementation).
- 2026-03-12 STL syntax session continued: started ranges pipeline rewrite drill in `src/stl_syntax/ranges_pipeline_rewrite.cpp` with loop + ranges stubs and parity test harness (fail-first baseline: 3/6 passing).
- 2026-03-12 STL syntax session continued: completed ranges pipeline rewrite drill with loop and `filter | transform | take` implementations; parity harness passing (6/6). Added stronger constraint for formatter helper (`bidirectional_range` + `common_range`) to match `prev(end)` usage.
