#include "bits/stdc++.h"

using namespace std;

void solve(int test) {
    int p;
    
    cin >> p;

    vector<int> arr;

    for(int k = 1; k * k <= p; ++k) {
        if(p % k) continue;
        arr.push_back(k);
        if(k * k != p) arr.push_back(p / k);
    }

    sort(arr.begin(), arr.end());

    int n = arr.size();
    const int INF = 1e9;

    vector<array<int, 42>> dp(n), target(n);
    
    for(int i = 0; i < n; ++i) {
        dp[i].fill(INF);
        target[i].fill(-1);
    }

    for(int i = 0; i <= 41; ++i) dp.back()[i] = i;

    for(int i = n - 1; i >= 0; --i) {
        int divisor = arr[i];

        for(int s = 0; s <= 41; ++s) {
            for(int x = 2; s + x <= 41; ++x) {
                if(divisor % x) continue;

                int pos = lower_bound(arr.begin(), arr.end(), divisor / x) - arr.begin();

                if(dp[pos][s + x] > dp[i][s] + 1) {
                    dp[pos][s + x] = 1 + dp[i][s];
                    target[pos][s + x] = x;
                }
            }
        }
    }

    cout << "Case #" << test << ": ";

    if(dp[0][41] == INF) {
        cout << "-1\n";
        return;
    }

    vector<int> ans;

    int a = 1, b = 41;

    while(a < p) {
        int pos = lower_bound(arr.begin(), arr.end(), a) - arr.begin();
        int x = target[pos][b];
        ans.push_back(x);
        a *= x;
        b -= x;
    }

    while(b--) ans.push_back(1);

    cout << ans.size();
    for(int x : ans) cout << ' ' << x;
    cout << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin >> t;

    for(int i = 1; i <= t; ++i) solve(i);

    return 0;
}

