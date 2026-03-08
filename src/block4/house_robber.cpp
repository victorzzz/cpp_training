#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::vector;

struct TestCase
{
    vector<int> nums;
    int expected;
};

vector<TestCase> test_cases{
    {{1, 2, 3, 1}, 4},
    {{2, 7, 9, 3, 1}, 12},

    {{}, 0},
    {{5}, 5},
    {{2, 1}, 2},
    {{0, 0, 0}, 0},
    {{2, 1, 1, 2}, 4},
};

int robMaxMoneyImplMemoization(const vector<int> &nums, int startPosition, vector<int> &cache);
int robMaxMoneyImpl(const vector<int> &nums, int startPosition, vector<int> &cache);
int robMaxMoneyRollingDP(const vector<int> &nums);

int robMaxMoney(const vector<int> &nums)
{
    if (nums.empty())
    {
        return 0;
    }

    if (nums.size() == 1)
    {
        return nums[0];
    }

    if (nums.size() == 2)
    {
        return std::max(nums[0], nums[1]);
    }

    vector<int> cache(nums.size(), -1);

    return robMaxMoneyImplMemoization(nums, 0, cache);
}

int robMaxMoneyImplMemoization(const vector<int> &nums, int startPosition, vector<int> &cache)
{
    if (cache[startPosition] != -1)
    {
        return cache[startPosition];
    }

    int result = robMaxMoneyImpl(nums, startPosition, cache);

    cache[startPosition] = result;

    return result;
}

int robMaxMoneyImpl(const vector<int> &nums, int startPosition, vector<int> &cache)
{
    if (startPosition == nums.size() - 1)
    {
        return nums[startPosition];
    }
    else
    {
        if (startPosition == nums.size() - 2)
        {
            return std::max(nums[startPosition], nums[startPosition + 1]);
        }
    }

    int result_minus_one = robMaxMoneyImplMemoization(nums, startPosition + 1, cache);
    int result_minus_two = robMaxMoneyImplMemoization(nums, startPosition + 2, cache);

    return std::max(nums[startPosition] + result_minus_two, result_minus_one);
}

int robMaxMoneyRollingDP(const vector<int> &nums)
{
    int next1 = 0; // dp[i + 1]
    int next2 = 0; // dp[i + 2]

    for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i)
    {
        int cur = std::max(nums[i] + next2, next1);
        next2 = next1;
        next1 = cur;
    }

    return next1;
}

template <typename T>
string vecToString(const vector<T> &vec)
{
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        ss << vec[i];
        if (i + 1 < vec.size())
        {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

int main()
{
    for (const auto &test_case : test_cases)
    {
        int answer = robMaxMoney(test_case.nums);
        bool is_correct = (answer == test_case.expected);

        std::cout << "nums=" << vecToString(test_case.nums)
                  << " => answer=" << answer
                  << ", expected=" << test_case.expected
                  << ", correct=" << is_correct << '\n';
    }

    return 0;
}
