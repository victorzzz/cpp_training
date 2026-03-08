#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <queue>

using std::pair;
using std::string;
using std::vector;

struct TestCase
{
    int numCourses;
    vector<pair<int, int>> prerequisites;
    bool expected;
};

// Pairs are (a, b): to take course a, you must first take b.
vector<TestCase> test_cases{
    {2, {{1, 0}}, true},
    {2, {{1, 0}, {0, 1}}, false},
    {5, {{1, 0}, {2, 0}, {3, 1}, {3, 2}, {4, 3}}, true},
    {4, {{1, 0}, {2, 1}, {0, 2}}, false},
};

bool canFinishCourses(int numCourses, const vector<pair<int, int>> &prerequisites)
{
    if (numCourses <= 0)
    {
        return true;
    }

    // Build graph as b -> a for each prerequisite pair (a, b).
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    for (const auto &p : prerequisites)
    {
        int a = p.first;
        int b = p.second;

        if (a < 0 || a >= numCourses || b < 0 || b >= numCourses)
        {
            return false;
        }

        graph[b].push_back(a);
        ++indegree[a];
    }

    std::queue<int> q;
    for (int course = 0; course < numCourses; ++course)
    {
        if (indegree[course] == 0)
        {
            q.push(course);
        }
    }

    int processed = 0;
    while (!q.empty())
    {
        int course = q.front();
        q.pop();
        ++processed;

        for (int next : graph[course])
        {
            --indegree[next];
            if (indegree[next] == 0)
            {
                q.push(next);
            }
        }
    }

    return processed == numCourses;
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

string prereqToString(const vector<pair<int, int>> &prerequisites)
{
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < prerequisites.size(); ++i)
    {
        ss << "[" << prerequisites[i].first << ", " << prerequisites[i].second << "]";
        if (i + 1 < prerequisites.size())
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
        bool answer = canFinishCourses(test_case.numCourses, test_case.prerequisites);
        bool is_correct = (answer == test_case.expected);

        std::cout << "numCourses=" << test_case.numCourses
                  << ", prerequisites=" << prereqToString(test_case.prerequisites)
                  << " => answer=" << answer
                  << ", expected=" << test_case.expected
                  << ", correct=" << is_correct << '\n';
    }

    return 0;
}
