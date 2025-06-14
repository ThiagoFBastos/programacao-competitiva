#include "bits/stdc++.h"

using namespace std;

using ll = long long;

const int cnt[] = {(int)2e5, (int)3e5, (int)4e5};
const int N = 1e5;

void solve() {
    int n;
    
    cin >> n;
    
    vector<ll> tim(n), pre(n + 1, 0);
    
    for(ll& t : tim) cin >> t;
    
    sort(tim.begin(), tim.end());
    
    for(int i = 1; i <= n; ++i) {
        ll dp = 0;
        for(int j = 0; j < 3; ++j) {
            int k = upper_bound(tim.begin(), tim.end(), tim[i - 1] - cnt[j]) - tim.begin() - 1;
            if(k < 0) break;
            dp = max(dp, cnt[j] / N + pre[k + 1]);
        }
        pre[i] = max(pre[i - 1], dp);
    }
    
    cout << pre.back() + 4 << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}
