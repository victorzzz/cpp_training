#include <array>
#include <concepts>
#include <iostream>
#include <list>
#include <ranges>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

// Drill: Implement a concepts-gated sum_range utility.
// Assumptions: sum result type is the range's value_type; empty range sums to 0.
// Sample inputs: [1,2,3], [10,-5,7], std::list<short>{4,6}, std::array<long, 0>{}

struct TestCase
{
    std::string name;
    long long expected;
    long long actual;
};

template <typename R>
concept ArithmeticInputRange =
    std::ranges::input_range<R> &&
    std::is_arithmetic_v<std::ranges::range_value_t<R>>;

template <ArithmeticInputRange R>
auto sum_range(R &&range)
{
    using Value = std::ranges::range_value_t<std::remove_cvref_t<R>>;

    Value total{};

    for (const auto &i : range)
    {
        total += i;
    }

    return total;
}

int main()
{
    const std::vector<int> v1{1, 2, 3, 4};
    const std::vector<int> v2{10, -5, 7};
    const std::list<short> l1{4, 6};
    const std::array<long, 0> empty{};
    std::istringstream iss("3 4 5");
    auto input_view = std::ranges::istream_view<int>(iss);

    std::vector<TestCase> tests{
        {"normal/vector increasing", 10, static_cast<long long>(sum_range(v1))},
        {"normal/vector mixed sign", 12, static_cast<long long>(sum_range(v2))},
        {"normal/list short", 10, static_cast<long long>(sum_range(l1))},
        {"normal/input_range istream_view", 12, static_cast<long long>(sum_range(input_view))},
        {"edge/empty range", 0, static_cast<long long>(sum_range(empty))},
    };

    int passed = 0;
    for (const auto &test : tests)
    {
        const bool ok = (test.expected == test.actual);
        if (ok)
        {
            ++passed;
        }

        std::cout << test.name << " | expected=" << test.expected
                  << " actual=" << test.actual
                  << " => " << (ok ? "PASS" : "FAIL") << '\n';
    }

    // Compile-time acceptance checks.
    static_assert(requires(const std::vector<int> &v) { sum_range(v); });
    static_assert(requires(const std::list<double> &v) { sum_range(v); });
    static_assert(requires(std::istringstream &stream) { sum_range(std::ranges::istream_view<int>(stream)); });

    // Compile-time rejection checks.
    static_assert(!ArithmeticInputRange<std::vector<std::string>>);

    std::cout << "Passed " << passed << "/" << tests.size() << " tests." << '\n';
    return (passed == static_cast<int>(tests.size())) ? 0 : 1;
}
