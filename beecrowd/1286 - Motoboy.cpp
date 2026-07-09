#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int INF = 1'000'000'000;

    while(true) {
        int n, max_pizzas;

        cin >> n;

        if(n == 0)
            break;

        cin >> max_pizzas;

        vector<int> dp(max_pizzas + 1, -INF);

        auto rng = views::iota(0, n) | views::transform([](auto) {
            int total_time;
            int quantity;

            cin >> total_time >> quantity;

            return make_pair(total_time, quantity);
        });

        dp[0] = 0;

        for(const auto&& [t, v] : rng)
            for(int i = max_pizzas - v; i >= 0; --i)
                dp[i + v] = max(dp[i + v], dp[i] + t);
        

        int answer = *max_element(dp.begin(), dp.end());

        cout << answer << " min.\n";
    }

    return 0;
}