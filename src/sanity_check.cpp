#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> nums{1, 2, 3, 4, 5, 6};
    auto evens = nums | std::views::filter([](int x) { return x % 2 == 0; });

    int sum = 0;
    for (int x : evens) {
        sum += x;
    }

    std::cout << "C++20 sanity check, sum of evens = " << sum << '\n';
    return 0;
}
