#include <algorithm>
#include <exception>
#include <functional>
#include <future>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

// Drill rules:
// 1. Implement parallel_sum_async with std::async and std::future.
// 2. Use std::launch::async explicitly.
// 3. Synchronize by collecting futures and calling get().
// 4. Before coding, explain time complexity, launch policy behavior, and failure modes.

struct TestResult
{
    std::string name;
    bool passed;
    std::string detail;
};

long long sum_range(const std::vector<int> &values, std::size_t begin, std::size_t end)
{
    if (begin > end || end > values.size())
    {
        throw std::out_of_range("invalid sum_range bounds");
    }

    return std::accumulate(values.begin() + static_cast<std::ptrdiff_t>(begin),
                           values.begin() + static_cast<std::ptrdiff_t>(end),
                           0LL);
}

long long parallel_sum_async(const std::vector<int> &values, int task_count)
{
    if (task_count <= 0)
    {
        throw std::invalid_argument("task_count <= 0");
    }

    if (values.empty())
    {
        return 0LL;
    }

    size_t batch_size = 0;
    if (values.size() < task_count)
    {
        batch_size = 1;
        task_count = static_cast<int>(values.size());
    }
    else
    {
        batch_size = values.size() / task_count + ((values.size() % task_count) == 0 ? 0 : 1);
    }

    std::vector<std::future<long long>> futures{};
    futures.reserve(task_count);

    for (int i = 0; i < task_count; ++i)
    {
        size_t begin = batch_size * i;

        if (begin > values.size())
        {
            break;
        }

        size_t end = std::min(batch_size * (i + 1), values.size());

        if (begin > end || end > values.size())
        {
            throw std::out_of_range("invalid sum_range bounds");
        }

        futures.push_back(std::async(std::launch::async, [&values](std::size_t begin, std::size_t end)
                                     { return sum_range(values, begin, end); }, begin, end));
    }

    // - reject task_count <= 0 with std::invalid_argument
    // - return 0 for an empty input vector
    // - split the work into contiguous chunks
    // - launch each chunk with std::async(std::launch::async, ...)
    // - collect results with future.get() and return the total

    long long result = 0;

    for (auto &f : futures)
    {
        result += f.get();
    }

    return result;
}

long long parallel_sum_async_nice(const std::vector<int> &values, int task_count)
{
    if (task_count <= 0)
    {
        throw std::invalid_argument("task_count must be positive");
    }

    if (values.empty())
    {
        return 0LL;
    }

    const std::size_t total_elements = values.size();
    const std::size_t actual_task_count =
        std::min<std::size_t>(static_cast<std::size_t>(task_count), total_elements);
    const std::size_t base_chunk_size = total_elements / actual_task_count;
    const std::size_t remainder = total_elements % actual_task_count;

    std::vector<std::future<long long>> futures;
    futures.reserve(actual_task_count);

    std::size_t begin = 0;
    for (std::size_t task_index = 0; task_index < actual_task_count; ++task_index)
    {
        const std::size_t extra = (task_index < remainder) ? 1U : 0U;
        const std::size_t end = begin + base_chunk_size + extra;

        futures.push_back(std::async(std::launch::async,
                                     sum_range,
                                     std::cref(values),
                                     begin,
                                     end));

        begin = end;
    }

    long long total = 0;
    for (auto &future : futures)
    {
        total += future.get();
    }

    return total;
}

TestResult expect_equal(const std::string &name, long long expected, long long actual)
{
    return {
        name,
        expected == actual,
        "expected=" + std::to_string(expected) + " actual=" + std::to_string(actual)};
}

TestResult expect_equal_or_exception(const std::string &name,
                                     long long expected,
                                     const std::vector<int> &values,
                                     int task_count)
{
    try
    {
        return expect_equal(name, expected, parallel_sum_async(values, task_count));
    }
    catch (const std::exception &ex)
    {
        return {name, false, "threw exception: " + std::string(ex.what())};
    }
    catch (...)
    {
        return {name, false, "threw non-standard exception"};
    }
}

TestResult expect_equal_or_exception_nice(const std::string &name,
                                          long long expected,
                                          const std::vector<int> &values,
                                          int task_count)
{
    try
    {
        return expect_equal(name, expected, parallel_sum_async_nice(values, task_count));
    }
    catch (const std::exception &ex)
    {
        return {name, false, "threw exception: " + std::string(ex.what())};
    }
    catch (...)
    {
        return {name, false, "threw non-standard exception"};
    }
}

TestResult expect_throws_invalid_argument(const std::string &name, const std::vector<int> &values, int task_count)
{
    try
    {
        (void)parallel_sum_async(values, task_count);
        return {name, false, "expected std::invalid_argument"};
    }
    catch (const std::invalid_argument &)
    {
        return {name, true, "caught std::invalid_argument"};
    }
    catch (const std::exception &ex)
    {
        return {name, false, "caught different exception: " + std::string(ex.what())};
    }
    catch (...)
    {
        return {name, false, "caught non-standard exception"};
    }
}

int main()
{
    const std::vector<int> a{1, 2, 3, 4};
    const std::vector<int> b{10, -5, 8, -3, 6};
    const std::vector<int> c{42};
    const std::vector<int> d{1, 2, 3, 4, 5};
    const std::vector<int> e{3, 1, 4, 1, 5, 9, 2, 6};
    const std::vector<int> f{1, 2, 3, 4, 5, 6, 7};
    const std::vector<int> empty{};

    std::vector<TestResult> tests;
    tests.push_back(expect_equal_or_exception("current/small even split", 10, a, 2));
    tests.push_back(expect_equal_or_exception("current/mixed signs", 16, b, 3));
    tests.push_back(expect_equal_or_exception("current/more tasks than elements", 42, c, 4));
    tests.push_back(expect_equal_or_exception("current/uneven split 5 elements 4 tasks", 15, d, 4));
    tests.push_back(expect_equal_or_exception("current/uneven split 8 elements 3 tasks", 31, e, 3));
    tests.push_back(expect_equal_or_exception("current/uneven split 7 elements 5 tasks", 28, f, 5));
    tests.push_back(expect_equal_or_exception("current/empty input returns zero", 0, empty, 2));
    tests.push_back(expect_throws_invalid_argument("current/zero tasks throws", a, 0));
    tests.push_back(expect_equal_or_exception_nice("nice/small even split", 10, a, 2));
    tests.push_back(expect_equal_or_exception_nice("nice/mixed signs", 16, b, 3));
    tests.push_back(expect_equal_or_exception_nice("nice/more tasks than elements", 42, c, 4));
    tests.push_back(expect_equal_or_exception_nice("nice/uneven split 5 elements 4 tasks", 15, d, 4));
    tests.push_back(expect_equal_or_exception_nice("nice/uneven split 8 elements 3 tasks", 31, e, 3));
    tests.push_back(expect_equal_or_exception_nice("nice/uneven split 7 elements 5 tasks", 28, f, 5));
    tests.push_back(expect_equal_or_exception_nice("nice/empty input returns zero", 0, empty, 2));
    tests.push_back(expect_equal_or_exception_nice("nice/many tasks one element", 42, c, 100));

    int passed = 0;
    for (const auto &test : tests)
    {
        if (test.passed)
        {
            ++passed;
        }

        std::cout << test.name << " | " << test.detail
                  << " => " << (test.passed ? "PASS" : "FAIL") << '\n';
    }

    std::cout << "Passed " << passed << "/" << tests.size() << " tests." << '\n';

    return (passed == static_cast<int>(tests.size())) ? 0 : 1;
}
