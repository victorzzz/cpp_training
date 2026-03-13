#include <exception>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

// Drill rules:
// 1. Implement run_locked_counter with std::thread, std::mutex, and std::lock_guard.
// 2. Do not use std::atomic, condition_variable, async, or concepts in this drill.
// 3. Keep this MSVC C++20 compatible.
// 4. Before coding, explain time complexity, synchronization strategy, and failure modes.

struct TestResult
{
    std::string name;
    bool passed;
    std::string detail;
};

struct JoinThreadsOnExit
{
    std::vector<std::thread> &threads;

    void join_all()
    {
        for (auto &thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

    ~JoinThreadsOnExit()
    {
        join_all();
    }
};

int run_locked_counter(int thread_count, int increments_per_thread)
{
    if (thread_count < 0)
    {
        throw std::invalid_argument("thread_count must be non-negative");
    }

    if (increments_per_thread < 0)
    {
        throw std::invalid_argument("increments_per_thread must be non-negative");
    }

    std::mutex mutex;
    int counter = 0;
    std::vector<std::thread> threads;
    threads.reserve(thread_count);
    JoinThreadsOnExit joiner{threads};

    for (int thread_index = 0; thread_index < thread_count; ++thread_index)
    {
        threads.emplace_back([&mutex, &counter, increments_per_thread]()
                             {
                                 for (int increment = 0; increment < increments_per_thread; ++increment)
                                 {
                                     std::lock_guard<std::mutex> lock(mutex);
                                     ++counter;
                                 }
                             });
    }

    joiner.join_all();
    return counter;
}

int run_racy_counter_once(int thread_count, int increments_per_thread)
{
    int counter = 0;
    std::vector<std::thread> workers;
    workers.reserve(thread_count);

    for (int t = 0; t < thread_count; ++t)
    {
        workers.emplace_back([&counter, increments_per_thread]()
                             {
                                 for (int i = 0; i < increments_per_thread; ++i)
                                 {
                                     ++counter;
                                 } });
    }

    for (auto &worker : workers)
    {
        worker.join();
    }

    return counter;
}

bool observe_race_condition(int attempts, int thread_count, int increments_per_thread)
{
    const int expected = thread_count * increments_per_thread;

    for (int attempt = 0; attempt < attempts; ++attempt)
    {
        if (run_racy_counter_once(thread_count, increments_per_thread) != expected)
        {
            return true;
        }
    }

    return false;
}

TestResult expect_equal(const std::string &name, int expected, int actual)
{
    return {
        name,
        expected == actual,
        "expected=" + std::to_string(expected) + " actual=" + std::to_string(actual)};
}

TestResult expect_throws_invalid_argument(const std::string &name, int thread_count, int increments_per_thread)
{
    try
    {
        (void)run_locked_counter(thread_count, increments_per_thread);
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
    std::vector<TestResult> tests;
    tests.push_back(expect_equal("single thread exact count", 7, run_locked_counter(1, 7)));
    tests.push_back(expect_equal("zero threads returns zero", 0, run_locked_counter(0, 100)));
    tests.push_back(expect_equal("multi-thread exact count", 200000, run_locked_counter(4, 50000)));
    tests.push_back(expect_throws_invalid_argument("negative thread count throws", -1, 10));
    tests.push_back(expect_throws_invalid_argument("negative increments throws", 2, -5));

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

    std::cout << "Passed " << passed << "/" << tests.size() << " correctness tests." << '\n';

    const bool race_observed = observe_race_condition(8, 8, 200000);
    std::cout << "race demo | expected some runs to lose updates"
              << " => " << (race_observed ? "OBSERVED" : "NOT OBSERVED THIS TIME") << '\n';

    return (passed == static_cast<int>(tests.size())) ? 0 : 1;
}
