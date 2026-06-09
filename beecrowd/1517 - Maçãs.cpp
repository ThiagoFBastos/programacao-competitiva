#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    using point = pair<int, int>;
    using apple = tuple<int, int, int>;

    constexpr int INF = 1e9;
    size_t n, m, k;

    auto distance = [](const point& p, const point& q) {
        auto [x0, y0] = p;
        auto [x1, y1] = q;

        int dx = abs(x0 - x1);
        int dy = abs(y0 - y1);

        if(dx < dy) dy -= dx;
        else dx -= dy;

        return dx + dy;
    };

    while(cin >> n >> m >> k && n && m && k) {
        vector<apple> apples(k + 1);

        for(size_t i = 1; i <= k; ++i) {
            int x, y, t;

            cin >> x >> y >> t;

            apples[i] = {x, y, t};
        }

        int x0, y0;

        cin >> x0 >> y0;

        apples[0] = {x0, y0, 0};

        vector<int> dp(k + 1, -INF);
        int answer {};

        dp[0] = 0;

        for(size_t i = 1; i <= k; ++i) {
            auto [xf, yf, tf] = apples[i];

            for(size_t j = 0; j < i; ++j) {
                auto [xi, yi, ti] = apples[j];

                if(distance({xi, yi}, {xf, yf}) <= tf - ti)
                    dp[i] = max(dp[i], dp[j] + 1);
            }

            answer = max(answer, dp[i]);
        }

        cout << answer << '\n';
    }

    return 0;
}