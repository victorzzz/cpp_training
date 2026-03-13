# Section Progress: Concurrency and Performance

## Goals

- Understand core thread safety patterns for interviews
- Explain lock-based vs lock-free trade-offs at high level
- Avoid over-engineering under time pressure

## Checklist

- [x] `std::thread` and `std::async` basics reviewed
- [x] Mutex usage pitfalls reviewed
- [x] Race condition examples reasoned through
- [ ] Performance discussion practice completed

## Coding Tasks (Practical Drills)

- Producer-consumer queue (mutex + condition variable):
 	- Implement bounded queue with `push`/`pop` blocking semantics.
 	- Target: no data races, no busy waiting.
- `std::async` vs `std::thread` comparison task:
 	- Parallel sum of 1e7 integers.
 	- Report launch policy behavior and synchronization approach.
 	- Target: explain overhead trade-offs clearly.
- Race-condition debugging drill:
 	- Start from intentionally racy counter increment.
 	- Fix with `std::mutex`, then with `std::atomic<int>`.
 	- Target: identify correctness first, then performance discussion.

## Session Log

- 2026-03-04: Section initialized.
- 2026-03-12: Started Day 5 with a fail-first counter drill using `std::thread`, `std::mutex`, and `std::lock_guard`.
- 2026-03-12: Implemented `run_locked_counter` in `src/concurrency/counter_race_drill.cpp`; verified negative-input handling, exact final count, and MSVC C++20 compatibility (`5/5` correctness tests passing).
- 2026-03-12: Intentional racy counter demo produced lost updates, reinforcing why unsynchronized shared increments are incorrect even when code sometimes appears to work.
- 2026-03-12: Added fail-first `std::async` drill in `src/concurrency/async_parallel_sum_drill.cpp` for contiguous-chunk parallel sum with explicit `std::launch::async` and `std::future::get()` synchronization (`0/5` passing baseline).
- 2026-03-12: Added `parallel_sum_async_nice` as a reference implementation that caps task count to input size and distributes the remainder across early chunks; verified side-by-side with the existing function (`16/16` total tests passing).
- 2026-03-12: Switched to the error-handling half of Day 5 with `src/error_handling/timeout_parser_drill.cpp`, a fail-first `std::from_chars` parser returning `std::optional<int>` plus a throwing wrapper (`6/11` baseline).

## Mistake Log

- 2026-03-12: First implementation batched `increments_per_thread` into one locked addition per worker, which passed the harness but did not satisfy the drill requirement of `N` synchronized increments per thread.
- 2026-03-12: Initial RAII joiner version returned the counter before joining workers; corrected by joining before reading the final result while retaining cleanup for exceptional thread-launch paths.
