#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

struct TestCase
{
    vector<int> coins;
    int amount;
    int expected;
};

vector<TestCase> test_cases{
    // Normal cases
    {{1, 2, 5}, 11, 3},
    {{2, 4}, 8, 2},
    {{2, 5, 10, 1}, 27, 4},

    // Edge / corner cases
    {{2}, 3, -1},
    {{1}, 0, 0},
    {{}, 0, 0},
    {{}, 7, -1},
    {{3, 7}, 1, -1},
};

int minCoins(const vector<int> &coins, int amount)
{
    // TODO: Implement DP solution for Coin Change.
    (void)coins;
    (void)amount;
    return -999;
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
        int answer = minCoins(test_case.coins, test_case.amount);
        bool is_correct = (answer == test_case.expected);

        std::cout << "coins=" << vecToString(test_case.coins)
                  << ", amount=" << test_case.amount
                  << " => answer=" << answer
                  << ", expected=" << test_case.expected
                  << ", correct=" << is_correct << '\n';
    }

    return 0;
}
