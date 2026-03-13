#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <algorithm>

struct TestCase
{
    std::vector<std::string> words;
    int k;
    std::vector<std::string> expected_result;
};

std::vector<TestCase> test_cases{
    // Normal cases
    {{"aa", "bb", "cc", "aa", "bb", "aa", "dd", "ab", "bb", "cc"}, 3, {"aa", "bb", "cc"}},

    // Edge cases
    {{}, 5, {}},
    {{"aa"}, 5, {"aa"}},
};

std::vector<std::string> top_k_frequent_words_with_partial_sort(
    const std::vector<std::string> &words,
    int k)
{
    if (k <= 0 || words.empty())
    {
        return {};
    }

    std::unordered_map<std::string, int> word_count_map;

    for (const auto &word : words)
    {
        word_count_map[word]++;
    }

    std::vector<std::pair<std::string, int>> items(word_count_map.size());
    std::copy(word_count_map.begin(), word_count_map.end(), items.begin());

    auto min_k = std::min(k, static_cast<int>(word_count_map.size()));

    std::partial_sort(items.begin(), items.begin() + min_k, items.end(),
                      [](const auto &arg1, const auto &arg2)
                      {
                          if (arg1.second == arg2.second)
                          {
                              return arg1.first < arg2.first;
                          }

                          return arg1.second > arg2.second;
                      });

    std::vector<std::string> result;
    result.reserve(min_k);

    for (auto item = items.begin(); item < items.begin() + min_k; ++item)
    {
        result.push_back(item->first);
    }

    return result;
}

std::vector<std::string> top_k_frequent_words(
    const std::vector<std::string> &words,
    int k)
{
    if (k <= 0 || words.empty())
    {
        return {};
    }

    std::unordered_map<std::string, int> word_count_map;

    for (const auto &word : words)
    {
        word_count_map[word]++;
    }

    std::vector<std::pair<std::string, int>> entries;
    entries.reserve(word_count_map.size());

    for (const auto &entry : word_count_map)
    {
        entries.push_back(entry);
    }

    std::sort(entries.begin(), entries.end(), [](const auto &a, const auto &b)
              {
                  if (a.second != b.second)
                  {
                      return a.second > b.second;
                  }
                  return a.first < b.first; });

    const int limit = std::min(k, static_cast<int>(entries.size()));
    std::vector<std::string> result;
    result.reserve(limit);

    for (int i = 0; i < limit; ++i)
    {
        result.push_back(entries[i].first);
    }

    return result;
}

template <typename T>
std::string vecToString(const std::vector<T> &vec)
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
    int passed = 0;

    for (const auto &test_case : test_cases)
    {
        auto result = top_k_frequent_words_with_partial_sort(test_case.words, test_case.k);
        const bool ok = (result == test_case.expected_result);
        if (ok)
        {
            ++passed;
        }

        std::cout << "words:" << vecToString(test_case.words) << "; k:" << test_case.k << "; "
                  << "expected:" << vecToString(test_case.expected_result) << "; "
                  << "result:" << vecToString(result) << "; "
                  << (ok ? "PASS" : "FAIL") << std::endl;
    }

    std::cout << "Passed " << passed << "/" << test_cases.size() << " tests." << std::endl;
}