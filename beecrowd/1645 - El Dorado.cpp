#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e2 + 5;

long long dp[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while(true) {
        int n, m;

        cin >> n >> m;

        if(n + m == 0)
            break;

        vector<int> values(n);

        for(auto& val : values)
            cin >> val;

        for(int i = 0; i < n; ++i)
            for(int j = 1; j <= m; ++j)
                dp[i][j] = 0;

        long long answer {};

        for(int i = 0; i < n; ++i) {
            dp[i][1] = 1;
            for(int j = 0; j < i; ++j) {
                if(values[j] >= values[i])
                    continue;

                for(int k = 1; k <= min(m, i); ++k)
                    dp[i][k + 1] += dp[j][k];
            }

            answer += dp[i][m];
        }

        cout << answer << '\n';
    }
    return 0;
}