#include <bits/stdc++.h>

using namespace std;

long long removal_game(const std::vector<int>& nums)
{
    const auto n = nums.size();
    const auto sum = std::accumulate(nums.begin(), nums.end(), 0LL);
    constexpr long long INF = 0x1000000000000LL;

    std::vector<std::array<long long, 2>> dp(n, {0LL, 0LL});

    std::size_t turn = ~n & 1;

    for(std::size_t i = 0; i < n; ++i)
        dp[i][turn] = nums[i];

    for(std::size_t len = n - 1; len > 0; --len)
    {
        turn ^= 1;

        std::size_t my = turn, your = turn ^ 1;

        for(std::size_t i = 0; i < len; ++i)
            dp[i][my] = -INF;

        for(std::size_t i = 0; i < len; ++i)
            dp[i][my] = std::max(dp[i][my], nums[i] - dp[i + 1][your]);

        for(std::size_t i = 0; i < len; ++i)
            dp[i][my] = std::max(dp[i][my], nums[i + n - len] - dp[i][your]);
    }

    return (sum + dp[0][0]) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for(size_t n; cin >> n; ) {
        vector<int> nums(n);

        for(int& value : nums)
            cin >> value;

        cout << removal_game(nums) << '\n';
    }

    return 0;
}