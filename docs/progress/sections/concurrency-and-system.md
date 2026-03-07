# Section Progress: Concurrency and Performance

## Goals

- Understand core thread safety patterns for interviews
- Explain lock-based vs lock-free trade-offs at high level
- Avoid over-engineering under time pressure

## Checklist

- [ ] `std::thread` and `std::async` basics reviewed
- [ ] Mutex usage pitfalls reviewed
- [ ] Race condition examples reasoned through
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

## Mistake Log

- None yet.
