#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

struct TestCase
{
    vector<int> nums;
    int expected;
};

vector<TestCase> test_cases{
    // Normal cases
    {{2, 3, 2}, 3},
    {{1, 2, 3, 1}, 4},

    // Edge cases
    {{}, 0},
    {{1}, 1},
    {{1, 2}, 2},
    {{1, 2, 1, 1}, 3},
    {{5, 1, 1, 5}, 6},
};

int robMaxMoney(const vector<int> &nums, int start, int end)
{
    int r1 = 0;
    int r2 = 0;

    for (auto i = end; i >= start; --i)
    {
        int r = std::max(nums[i] + r2, r1);

        r2 = r1;
        r1 = r;
    }

    return r1;
}

int robMaxMoneyCircular(const vector<int> &nums)
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

    int case1 = robMaxMoney(nums, 0, static_cast<int>(nums.size()) - 2);
    int case2 = robMaxMoney(nums, 1, static_cast<int>(nums.size()) - 1);

    return std::max(case1, case2);
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
        int answer = robMaxMoneyCircular(test_case.nums);
        bool is_correct = (answer == test_case.expected);

        std::cout << "nums=" << vecToString(test_case.nums)
                  << " => answer=" << answer
                  << ", expected=" << test_case.expected
                  << ", correct=" << is_correct << '\n';
    }

    return 0;
}
