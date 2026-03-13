#include <algorithm>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

// Drill: Rewrite loop logic into a C++20 ranges pipeline.
// Goal: Keep positives even numbers, square them, take first k, preserve order.
// Assumptions:
// 1) nums may be empty
// 2) nums may contain negatives and zero
// 3) k may be 0 or greater than the number of qualifying elements
//
// Before implementing, state explicitly:
// - Time complexity target
// - Extra space target
// - Interview readability trade-off (loop vs ranges)

struct TestCase
{
    std::string name;
    std::vector<int> nums;
    int k;
    std::vector<int> expected;
};

std::vector<int> even_positive_squares_loop(const std::vector<int> &nums, int k)
{
    // Target: O(n) time, O(min(k, qualifying_count)) output space.

    std::vector<int> result;

    if (k <= 0)
    {
        return result;
    }

    result.reserve(k);

    for (const auto &i : nums)
    {
        if (i > 0 && i % 2 == 0)
        {
            result.push_back(i * i);
        }

        if (result.size() == k)
        {
            break;
        }
    }

    return result;
}

std::vector<int> even_positive_squares_ranges(const std::vector<int> &nums, int k)
{
    // - std::views::filter
    // - std::views::transform
    // - std::views::take
    // Then materialize into std::vector<int>.

    auto result_view = nums | std::views::filter([](const auto &element)
                                                 { return element > 0 && element % 2 == 0; }) |
                       std::views::transform([](const auto &element)
                                             { return element * element; }) |
                       std::views::take(k);

    std::vector<int> result{};
    result.reserve(std::ranges::distance(result_view));
    std::ranges::copy(result_view, std::back_inserter(result));

    return result;
}

template <typename T>
std::string vec_to_string(const std::vector<T> &v)
{
    std::ostringstream out;
    out << "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        out << v[i];
        if (i + 1 < v.size())
        {
            out << ", ";
        }
    }
    out << "]";
    return out.str();
}

//

std::string range_to_string(const auto &i_range)
    requires std::ranges::bidirectional_range<decltype(i_range)> &&
             std::ranges::common_range<decltype(i_range)>
{
    std::ostringstream out;
    out << "[";

    if (!std::ranges::empty(i_range))
    {
        auto last_iter = std::prev(i_range.end());
        for (auto iter = i_range.begin(); iter != i_range.end(); ++iter)
        {
            out << *iter;
            if (iter != last_iter)
            {
                out << ", ";
            }
        }
    }
    out << "]";
    return out.str();
}

int main()
{
    const std::vector<TestCase> tests{
        // Normal cases
        {"normal/sample 1", {3, -2, 4, 0, 6, 7}, 2, {16, 36}},
        {"normal/sample 2 no matches", {-4, -2, 0, 1, 3}, 5, {}},
        {"normal/sample 3 k > size", {2, 8, 10}, 10, {4, 64, 100}},

        // Edge cases
        {"edge/empty input", {}, 3, {}},
        {"edge/k is zero", {2, 4, 6}, 0, {}},
        {"edge/ordering preserved", {8, 1, 4, 3, 2}, 3, {64, 16, 4}},
    };

    int passed = 0;

    for (const auto &t : tests)
    {
        const auto baseline = even_positive_squares_loop(t.nums, t.k);
        const auto ranges = even_positive_squares_ranges(t.nums, t.k);

        const bool baseline_matches_expected = (baseline == t.expected);
        const bool ranges_matches_expected = (ranges == t.expected);
        const bool versions_match = (baseline == ranges);

        const bool ok = baseline_matches_expected && ranges_matches_expected && versions_match;
        if (ok)
        {
            ++passed;
        }

        std::cout << t.name
                  << " | expected=" << range_to_string(t.expected)
                  << " | baseline=" << range_to_string(baseline)
                  << " | ranges=" << range_to_string(ranges)
                  << " | " << (ok ? "PASS" : "FAIL") << '\n';
    }

    std::cout << "Passed " << passed << "/" << tests.size() << " tests." << '\n';
    return (passed == static_cast<int>(tests.size())) ? 0 : 1;
}
