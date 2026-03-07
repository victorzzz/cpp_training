# Section Progress: Interview Problem Solving

## Goals

- Reach consistent medium-problem solve time under 30-35 min
- Communicate thought process clearly while coding
- Minimize bugs via structured testing

## Targets

- Easy: 12-16
- Medium: 20-25
- Hard: 3-5 (optional stretch)

## Checklist

- [x] Arrays/strings pattern set completed
- [ ] Two pointers/sliding window set completed
- [ ] Stack/queue/binary search set completed
- [ ] Trees/graphs set completed
- [ ] DP core set completed
- [ ] 4 timed mock interviews completed

## Coding Tasks (Practical Drills)

- Arrays/strings timed set (45 min):
  - Two Sum (target O(n) time, O(n) space).
  - Longest Substring Without Repeating Characters (target O(n) time).
- Pattern fluency set (60 min):
  - Daily Temperatures (monotonic stack, target O(n)).
  - Search in Rotated Sorted Array (binary search, target O(log n)).
- Tree/graph starter set (60 min):
  - Binary Tree Level Order Traversal (BFS, target O(n)).
  - Course Schedule (topological sort, target O(V+E)).
- Post-problem checklist for each solution:
  - State brute force and optimized approach.
  - State complexity before coding.
  - Run 3 edge cases before finalizing.

## Session Log

- 2026-03-04: Section initialized.
- 2026-03-06 (Day 1, Block 4, 30 min, live): Completed Two Sum + Longest Substring drills under strict format (approach, complexity, edge cases, correctness).
- 2026-03-06: Longest Substring implementation corrected to canonical one-pass sliding window after stale-map bug surfaced on `abcaefgh`.

## Mistake Log

- 2026-03-06: Two Sum complexity phrasing initially incorrect (`O(n) * O(log n)`); corrected to average `O(n)` time with hash-map lookups average `O(1)`, worst-case `O(n^2)` under collisions.
- 2026-03-06: Longest Substring bug from sharing stale `last_seen` state across restarted scans; fixed by monotonic `left` + single pass over `right`.
