#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <iterator>
#include <sstream>

// test cases
std::vector<std::pair<std::vector<float>, std::vector<size_t>>> test_cases{
    {{}, {}},                             // empty input array
    {{10}, {0}},                          // one input
    {{1, 2, 3, 4, 5}, {1, 1, 1, 1, 0}},   // increasing input
    {{7, 6, 5, 4, 3}, {0, 0, 0, 0, 0}},   // decreasing input
    {{10, 20, 3, 2, 1}, {1, 0, 0, 0, 0}}, // increasing / decreasing input
    {{10, 8, 5, 7, 9}, {0, 3, 1, 1, 0}},  // decreasing / increasing input
    {{10, 2, 3, 4, 5}, {0, 1, 1, 1, 0}},  // decreasing / increasing input
    {{73, 73, 74}, {2, 1, 0}},            // equal temps before warmer day
    {{70, 70, 70}, {0, 0, 0}},            // all equal temps

};

std::vector<size_t> getAnswer(const std::vector<float> &temperature)
{
    std::vector<size_t> result(temperature.size(), 0);

    std::vector<size_t> index_stack;

    for (auto i = 0; i < temperature.size(); ++i)
    {
        while (!index_stack.empty())
        {
            auto top_index = index_stack.back();
            auto top_stack_value = temperature[top_index];

            if (top_stack_value < temperature[i])
            {
                result[top_index] = i - top_index;
                index_stack.pop_back();
            }
            else
            {
                break;
            }
        }

        index_stack.push_back(i);
    }

    return result;
}

template <typename T>
std::string vecToString(const std::vector<T> &vec)
{
    std::stringstream ss;
    for (auto item : vec)
    {
        ss << item << ", ";
    }

    return ss.str();
}

int main()
{
    // test all cases
    for (const auto &test_case : test_cases)
    {
        auto answer = getAnswer(test_case.first);
        auto is_correct = (answer == test_case.second);
        std::cout << "[" << vecToString(test_case.first) << "] => [" << vecToString(answer) << "], expected [" << vecToString(test_case.second) << "] " << is_correct << std::endl;
    }
}