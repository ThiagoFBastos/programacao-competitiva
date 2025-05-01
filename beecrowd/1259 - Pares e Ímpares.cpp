#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n;

    std::cin >> n;

    std::vector<int> nums(n);

    for(int& val : nums)
        std::cin >> val;

    std::ranges::sort(nums);

    auto odd = nums | std::views::filter([](const int& val) {return val % 2 == 1;}) | std::views::reverse;
    auto even = nums | std::views::filter([](const int& val) {return val % 2 == 0;});

    for(int val : even)
        std::cout<<val<<'\n';

    for(int val : odd)
        std::cout<<val<<'\n';
    
    return 0;
}