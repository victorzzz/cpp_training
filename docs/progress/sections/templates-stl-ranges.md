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
- 2026-03-12 (STL syntax drill, live): Implemented Top-K Frequent Words using `unordered_map` counting + custom comparator ordering (frequency desc, lexicographic asc). Reviewed when to use `sort` vs `partial_sort` and clarified that comparator variants with equivalent logic are behaviorally identical.
- 2026-03-12 (STL syntax drill, continued): Switched to concepts exercise `sum_range` constrained by `std::ranges::input_range` and arithmetic value type. Added code-first runtime tests (normal + edge) and compile-time acceptance/rejection checks; scaffold intentionally fails runtime tests until implementation is completed.
- 2026-03-12 (STL syntax drill, continued): Added `ranges_pipeline_rewrite.cpp` scaffold for loop-vs-ranges parity (`filter | transform | take`) with 3 normal + 3 edge tests. Baseline intentionally fail-first until both implementations are filled.
- 2026-03-12 (STL syntax drill, continued): Completed `ranges_pipeline_rewrite.cpp`; both loop and ranges solutions implemented and validated against expected output + parity checks (6/6 passing). Also corrected helper contract by constraining `range_to_string` with `bidirectional_range` + `common_range` when using `prev(end)`.

## Reinforcement Needed

- Keep stating worst-case for hash-based containers explicitly in interview answers.
- Practice the map-value-type rule: associative container element type uses `const` key (`pair<const K, V>`), which cannot be reordered by sorting algorithms.
- Keep algorithm selection explicit: `sort` for full ordering, `partial_sort` for top-k ordered prefix, `nth_element` for partition-only selection.
- Keep answering complexity explicitly before coding (`sum_range`: target `O(n)` time, `O(1)` extra space).
- Keep input-validation policy explicit in interview answers (assumption-only vs defensive handling for values like `k < 0`).

## Mistake Log

- 2026-03-04: First answer omitted worst-case complexity and concrete memory behavior; corrected after re-prompt.
- 2026-03-12: Tried `partial_sort` on `vector<pair<const string, int>>` copied from map iterator `value_type`; failed because elements are non-assignable due to `const` key.
- 2026-03-12: Used `std::copy(..., items.end())` on an empty vector; corrected by using `back_inserter` or explicit `emplace_back` into `vector<pair<string, int>>`.
