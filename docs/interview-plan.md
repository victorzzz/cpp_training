# C++20 Interview Plan (8 Days, 28 Hours)

## Constraints

- Total time: 28 hours
- Days 1-5: 2 hours/day
- Days 6-8: 6 hours/day
- Goal: modern C++20 confidence + coding interview speed/accuracy

## Sections

1. Tooling and workflow in VS Code (Windows + MSVC)
2. Modern C++ core: value semantics, RAII, move semantics, smart pointers
3. STL and C++20: algorithms, iterators, ranges, lambdas, structured bindings
4. Templates and type system: function templates, class templates, concepts, `auto`
5. Concurrency and performance basics: threads, async, atomics basics, profiling mindset
6. Interview problem solving patterns: arrays/strings, hash maps, two pointers, sliding window, stack/queue, binary search, trees, graphs, DP
7. Mock interviews and communication: approach explanation, trade-offs, edge cases, testing

## Day-by-Day Plan

### Day 1 (2h) - Setup + Refresh

- 45 min: validate VS Code build/debug workflow with MSVC (`cl /std:c++20`)
- 45 min: refresh C++ syntax changes since C++11 to C++20 (high level)
- 30 min: solve 1 easy + 1 medium array/string problem

### Day 2 (2h) - Core Memory Model

- 50 min: RAII, ownership, lvalue/rvalue, move vs copy
- 40 min: smart pointers (`unique_ptr`, `shared_ptr`, `weak_ptr`) pitfalls
- 30 min: 2 interview problems focused on memory-safe design

### Day 3 (2h) - STL + Ranges

- 60 min: containers, complexity, iterator invalidation rules
- 30 min: C++20 ranges and common algorithms
- 30 min: 2 medium problems solved with STL-first approach

### Day 4 (2h) - Templates + Concepts

- 60 min: template refresher + type deduction + `constexpr` use cases
- 30 min: concepts and constraints in practical interview code
- 30 min: 1 medium + 1 medium-hard problem

### Day 5 (2h) - Concurrency + Error Handling

- 45 min: `std::thread`, `std::async`, mutex basics, race-condition patterns
- 45 min: exceptions vs return types (`std::optional`, `std::expected` discussion)
- 30 min: 1 concurrency-style reasoning question + 1 coding problem

### Day 6 (6h) - Problem Marathon I

- 2h: arrays, strings, hash maps, two pointers, sliding window
- 2h: stack/queue, intervals, binary search on answer
- 1h: timed mock interview (45 min coding + 15 min review)
- 1h: focused revision on mistakes logged during day

### Day 7 (6h) - Problem Marathon II

- 2h: trees (DFS/BFS, recursion patterns)
- 2h: graphs (traversal, topological sort, shortest path basics)
- 1h: dynamic programming patterns (1D, 2D, knapsack flavor)
- 1h: timed mock interview + communication feedback

### Day 8 (6h) - Final Simulation

- 2h: full mock interview set (2 rounds x 55 min)
- 1.5h: deep review of weak areas from progress files
- 1h: C++20 theory rapid-fire (language + STL + complexity)
- 1h: system/design style discussion for senior-level context
- 0.5h: final cheat sheet and interview-day checklist

## Daily Execution Template

1. 5 min: pick focus and constraints
2. 70-100 min: learning + implementation
3. 30-60 min: problem solving under time limit
4. 10 min: update progress files
