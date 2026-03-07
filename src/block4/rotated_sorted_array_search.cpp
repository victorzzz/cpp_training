#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <iterator>
#include <sstream>

using std::vector, std::pair;

// test cases
vector<pair<pair<vector<int>, int>, int>> test_cases{
    {{{}, 123}, -1},                                   // empty input
    {{{777}, 123}, -1},                                // single item, target missing
    {{{123}, 123}, 0},                                 // single item, target found
    {{{1, 2, 3, 123, 156, 178}, 123}, 3},              // no rotation, target present
    {{{1, 2, 3, 123, 156, 178}, 999}, -1},             // no rotation, target missing
    {{{4, 5, 6, 7, 0, 1, 2}, 0}, 4},                   // classic rotation, target right half
    {{{4, 5, 6, 7, 0, 1, 2}, 6}, 2},                   // classic rotation, target left half
    {{{4, 5, 6, 7, 0, 1, 2}, 3}, -1},                  // classic rotation, target missing
    {{{6, 7, 8, 1, 2, 3, 4, 5}, 8}, 2},                // rotation near middle, target left half
    {{{6, 7, 8, 1, 2, 3, 4, 5}, 2}, 4},                // rotation near middle, target right half
    {{{123, 156, 178, 1, 2, 3, 40, 50, 60}, 50}, 7},   // custom rotated ascending case
    {{{123, 156, 178, 1, 2, 3, 40, 50, 60}, 999}, -1}, // custom rotated, missing target
    {{{3, 1}, 1}, 1},                                  // 2-element rotation, target at right
    {{{3, 1}, 3}, 0},                                  // 2-element rotation, target at left

};

int findInRotatedVector(const vector<int> &vec, int target)
{
    if (vec.empty())
    {
        return -1;
    }

    int left = 0;
    int right = static_cast<int>(vec.size() - 1);

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (vec[mid] == target)
        {
            return mid;
        }

        auto is_left_sorted = vec[left] <= vec[mid];

        if (is_left_sorted)
        {
            if (vec[left] <= target && target < vec[mid])
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        else // right sorted
        {
            if (vec[right] >= target && target > vec[mid])
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }

    return -1;
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
        auto input = test_case.first;
        std::cout << "Starting [" << vecToString(input.first) << "], target: " << input.second << std::endl;

        int index;

        try
        {
            index = findInRotatedVector(input.first, input.second);
        }
        catch (const std::exception &ex)
        {
            std::cout << "Exception: " << ex.what() << std::endl;
            continue;
        }

        auto is_correct = (index == test_case.second);
        std::cout << "[" << vecToString(input.first) << "], target: " << input.second << "  => " << index << ", expected: " << test_case.second << "; " << (is_correct ? "CORRECT" : "INCORRECT") << std::endl;
    }
}