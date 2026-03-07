#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <utility>

using char_index_map = std::unordered_map<std::string::value_type, std::string::size_type>;

size_t maxSubstringWithoutDuplication(const std::string &s)
{
    size_t max_substr_len = 0;
    size_t left = 0;
    char_index_map last_seen;

    // Keep window [left, right] valid (all chars unique).
    for (size_t right = 0; right < s.size(); ++right)
    {
        auto ch = s[right];
        auto it = last_seen.find(ch);
        if (it != last_seen.end() && it->second >= left)
        {
            left = it->second + 1;
        }

        last_seen[ch] = right;

        size_t window_len = right - left + 1;
        if (window_len > max_substr_len)
        {
            max_substr_len = window_len;
        }
    }

    return max_substr_len;
}

int main()
{
    // case 1 - epty string

    std::cout << "<empty string>: " << maxSubstringWithoutDuplication("") << std::endl;

    // case 2 - all the same character

    const std::string str2 = "AAAAAAAA";
    std::cout << str2 << ": " << maxSubstringWithoutDuplication(str2) << std::endl;

    // case 3 - "ABABABABABA"

    const std::string str3 = "ABABABABABA";
    std::cout << str3 << ": " << maxSubstringWithoutDuplication(str3) << std::endl;

    // case 4 - sorted "aaaaaBBBBBBBBBBBBBB"

    const std::string str4 = "aaaaaBBBBBBBBBBBBBB";
    std::cout << str4 << ": " << maxSubstringWithoutDuplication(str4) << std::endl;

    // case 5 - "abcdefghahahah" - longest string at the begining

    const std::string str5 = "abcdefghahahah";
    std::cout << str5 << ": " << maxSubstringWithoutDuplication(str5) << std::endl;

    // case 6 - "qaqaqabcdefghklmnopr" longest string at the end

    const std::string str6 = "qaqaqabcdefghklmnopr";
    std::cout << str6 << ": " << maxSubstringWithoutDuplication(str6) << std::endl;

    // case 7 - longest string in the middle "qaqabcdefghklmnqaqa"

    const std::string str7 = "qaqabcdefghklmnqaqa";
    std::cout << str7 << ": " << maxSubstringWithoutDuplication(str7) << std::endl;

    // case 8 - canonical tricky case for left-bound updates: "abba" -> 2

    const std::string str8 = "abba";
    std::cout << str8 << ": " << maxSubstringWithoutDuplication(str8) << std::endl;

    // case 9 - canonical tricky case: "pwwkew" -> 3

    const std::string str9 = "pwwkew";
    std::cout << str9 << ": " << maxSubstringWithoutDuplication(str9) << std::endl;

    // case 10 - canonical tricky case: "dvdf" -> 3

    const std::string str10 = "dvdf";
    std::cout << str10 << ": " << maxSubstringWithoutDuplication(str10) << std::endl;

    // case 11 - canonical tricky case: "tmmzuxt" -> 5

    const std::string str11 = "tmmzuxt";
    std::cout << str11 << ": " << maxSubstringWithoutDuplication(str11) << std::endl;

    // case 12 - stale-map exposure candidate: "abcaefgh" -> 7

    const std::string str12 = "abcaefgh";
    std::cout << str12 << ": " << maxSubstringWithoutDuplication(str12) << std::endl;
}