# Section Progress: Modern C++ Core

## Goals

- Refresh ownership and lifetime rules
- Use RAII and move semantics naturally
- Avoid raw `new/delete` in interview code

## Checklist

- [x] Value categories and references reviewed
- [x] Rule of 0/3/5 refreshed
- [ ] Smart pointer scenarios practiced
- [x] Exception safety levels understood

## Coding Tasks (Practical Drills)

- Implement `Buffer` twice:
 	- Version A: raw pointer ownership (`new[]/delete[]`) with explicit Rule-of-5.
 	- Version B: Rule-of-0 using `std::vector<int>`.
 	- Compare code size, bug surface, and copy/move complexity.
- Implement `clone_and_append` API with strong exception guarantee.
 	- Input: `const std::vector<int>& src`, `int value`.
 	- Output: new vector with appended value.
 	- Target: O(n) time, no mutation of source on failure.
- Smart pointer ownership graph exercise:
 	- Build parent-child tree with `std::unique_ptr`.
 	- Build observer links with `std::weak_ptr` to break cycles.
 	- Target: no leaks; explain ownership in 60 seconds.

## Session Log

- 2026-03-04: Section initialized.
- 2026-03-04 Correction: Day 1 Block 2 notes were logged prematurely; moved back to pending until live practice is completed.
- 2026-03-04 (Day 1, Block 2, 30 min, live): Completed mini-lesson + short drills.
- Prompt review outcomes:
 	- `consume(a)`: copy from lvalue parameter source.
 	- `consume(std::move(a))`: move (move ctor selected when available).
 	- `consume(make_name())`: corrected from "move due to optimization" to direct construction/copy elision model.
- Ownership policy drill outcome:
 	- Chosen policy: Rule-of-0 refactor using STL container (`std::vector<int>` preferred over raw `new[]`).
 	- Complexity framing: copy O(n), move O(1) amortized metadata transfer.

## Reinforcement Needed

- Add one explicit smart-pointer cycle example (`shared_ptr` + `weak_ptr`) in next core session.

## Mistake Log

- 2026-03-04: Initially described prvalue argument passing as "move by compiler optimization"; corrected to copy elision/direct initialization model.
