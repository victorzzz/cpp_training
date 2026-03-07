#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>
#include <unordered_map>
#include <tuple>

// Given nums and target, return indices of two numbers summing to target (Two Sum).

std::vector<std::tuple<int, int>> getIndecesOfSumTwo(const std::vector<int> &nums, int target)
{
    std::vector<std::tuple<int, int>> result;

    // broot force idea: two nested loops, O(n^2)
    for (auto i = 0; i < nums.size() - 1; ++i)
    {
        for (auto j = i + 1; j < nums.size(); ++j)
        {
            if (nums[i] + nums[j] == target)
            {
                result.emplace_back(i, j);
            }
        }
    }

    return result;
}

std::vector<std::tuple<int, int>> getIndecesOfSumTwoOptimized(const std::vector<int> &nums, int target)
{
    std::vector<std::tuple<int, int>> result;

    // Keep all seen indices per value so duplicates can form all valid pairs.
    std::unordered_map<int, std::vector<int>> processed;

    for (int i = 0; i < static_cast<int>(nums.size()); ++i)
    {
        auto remain = target - nums[i];
        if (processed.contains(remain))
        {
            for (int j : processed[remain])
            {
                result.emplace_back(j, i);
            }
        }

        processed[nums[i]].push_back(i);
    }

    return result;
}

int main()
{
    // std::vector<int> nums{1, 2, 3, 4, 5, 6};
    std::vector<int> nums{-1, 1, 1, 9, -1, -9};
    int target = 0;

    auto indeces = getIndecesOfSumTwoOptimized(nums, target);

    if (indeces.empty())
    {
        std::cout << "Empty result" << std::endl;
    }

    else
    {
        for (const auto &[i, j] : indeces)
        {
            std::cout << i << ", " << j << std::endl;
        }
    }

    return 0;
}