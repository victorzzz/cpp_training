#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <iterator>
#include <sstream>
#include <queue>

using std::pair;
using std::string;
using std::vector;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val, TreeNode *left, TreeNode *right) : val(val), left(left), right(right)
    {
    }
};

// test cases
vector<pair<TreeNode *, vector<vector<int>>>> test_cases{
    {nullptr, {}}, // empty
    {new TreeNode(42, nullptr, nullptr), {{42}}},

    {new TreeNode(42,
                  new TreeNode(37, nullptr, nullptr),
                  nullptr),
     {{42}, {37}}},

    {new TreeNode(42,
                  nullptr,
                  new TreeNode(39, nullptr, nullptr)),
     {{42}, {39}}},

    {new TreeNode(42,
                  new TreeNode(37, nullptr, nullptr),
                  new TreeNode(39, nullptr, nullptr)),
     {{42}, {37, 39}}},

    {new TreeNode(42,
                  new TreeNode(37,
                               new TreeNode(155, nullptr, nullptr),
                               nullptr),
                  new TreeNode(39, nullptr, nullptr)),
     {{42}, {37, 39}, {155}}},

    {new TreeNode(42,
                  new TreeNode(37,
                               new TreeNode(155,
                                            new TreeNode(277, nullptr, nullptr),
                                            nullptr),
                               nullptr),
                  new TreeNode(39, nullptr, nullptr)),
     {{42}, {37, 39}, {155}, {277}}},

    {new TreeNode(42,
                  new TreeNode(37,
                               new TreeNode(155,
                                            new TreeNode(277, nullptr, nullptr),
                                            new TreeNode(377, nullptr, nullptr)),
                               nullptr),
                  new TreeNode(39,
                               new TreeNode(555,
                                            new TreeNode(666, nullptr, nullptr),
                                            nullptr),
                               nullptr)),
     {{42}, {37, 39}, {155, 555}, {277, 377, 666}}},

};

void getLevelOrderTraversalImpl(TreeNode *root, vector<vector<int>> &result, int level);

vector<vector<int>> getLevelOrderTraversal(TreeNode *root)
{
    vector<vector<int>> result;

    getLevelOrderTraversalImpl(root, result, 0);

    return result;
}

vector<vector<int>> getLevelOrderTraversalWithBFS(TreeNode *root)
{
    vector<vector<int>> result;

    if (root == nullptr)
    {
        return result;
    }

    std::queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        size_t level_size = q.size();
        vector<int> level_values;
        level_values.reserve(level_size);

        for (size_t i = 0; i < level_size; ++i)
        {
            TreeNode *node = q.front();
            q.pop();

            level_values.push_back(node->val);

            if (node->left != nullptr)
            {
                q.push(node->left);
            }

            if (node->right != nullptr)
            {
                q.push(node->right);
            }
        }

        result.push_back(std::move(level_values));
    }

    return result;
}

void getLevelOrderTraversalImpl(TreeNode *root, vector<vector<int>> &result, int level)
{
    if (root == nullptr)
    {
        return;
    }

    if (result.size() < level + 1)
    {
        result.emplace_back();
    }

    vector<int> &level_array = result[level];
    level_array.push_back(root->val);

    getLevelOrderTraversalImpl(root->left, result, level + 1);
    getLevelOrderTraversalImpl(root->right, result, level + 1);

    return;
}

template <typename T>
string vecToString(const vector<T> &vec)
{
    std::stringstream ss;
    for (auto item : vec)
    {
        ss << item << ", ";
    }

    return ss.str();
}

template <typename T>
string vec2ToString(const vector<vector<T>> &vec2)
{
    std::stringstream ss;

    for (const auto &vec : vec2)
    {
        ss << "{ " << vecToString(vec) << "}, ";
    }

    return ss.str();
}

int main()
{
    // test all cases
    for (const auto &test_case : test_cases)
    {
        auto answer = getLevelOrderTraversal(test_case.first);
        auto is_correct = (answer == test_case.second);

        std::cout << "[ " << vec2ToString(answer) << " ] , expected [ " << vec2ToString(test_case.second) << " ] ; correct: " << is_correct << std::endl;
    }
}