# Section Progress: Templates, STL, and Ranges

## Goals

- Use STL containers and algorithms with correct complexity
- Apply `ranges` and lambdas for clean solutions
- Explain iterator invalidation and container trade-offs

## Checklist

- [x] Container selection drills completed
- [ ] 10+ algorithm exercises with STL completed
- [x] C++20 ranges basics practiced
- [ ] Concepts syntax and use-cases refreshed

## Coding Tasks (Practical Drills)

- Container benchmark drill (interview-scale, not micro-benchmark):
  - Problem: 2e5 inserts + 2e5 membership queries.
  - Compare `std::vector` + sort + binary search vs `std::unordered_set`.
  - Target: report asymptotic costs and one practical trade-off.
- Ranges pipeline rewrite:
  - Convert loop-based filtering/transformation to `std::views::filter | std::views::transform`.
  - Preserve readability and correctness.
  - Target: same output as baseline tests.
- Concepts-gated utility:
  - Write `sum_range` constrained by `std::ranges::input_range` and arithmetic value type.
  - Target: compile-time rejection for unsupported types.

## Session Log

- 2026-03-04: Section initialized.
- 2026-03-04 Correction: Day 1 Block 3 notes were logged prematurely; moved back to pending until live practice is completed.
- 2026-03-04 (Day 1, Block 3, 30 min, live): Container trade-off drill completed with iterative correction.
- Final accepted framing from user:
 	- Primary: `std::unordered_set` for frequent membership queries with no ordering need.
 	- Alternative: `std::set`.
 	- Complexity: `unordered_set` average O(1), worst-case O(n); `set` O(log n).
 	- Memory behavior: `unordered_set` bucket array + per-node allocations + possible rehash spikes; `set` node pointer overhead + tree balancing costs.

## Reinforcement Needed

- Keep stating worst-case for hash-based containers explicitly in interview answers.

## Mistake Log

- 2026-03-04: First answer omitted worst-case complexity and concrete memory behavior; corrected after re-prompt.
