#include <bits/stdc++.h>

using namespace std;

const int64_t INFLL = 2e18;

void solve(int test) {
    int n, s;

    cin >> n >> s;

    set<tuple<int, int, int, int>> sweep;
    multiset<int64_t> ms;
    vector<int64_t> saved(n, -INFLL);
    int64_t save = 0, ans = 0;

    for(int i = 0; i < n; ++i) {
        int l, r, c;
        cin >> l >> r >> c;
        sweep.emplace(l, 0, c, i);
        sweep.emplace(r, 1, 0, i);
    }

    for(auto [p, type, c, k] : sweep) {
        if(type == 0) {
            if(!ms.empty()) save = max(save, *ms.rbegin() + (int64_t)s * p);
            ans = max(ans, save);
            int64_t value = save - (int64_t)s * p - c;
            ms.insert(value);
            saved[k] = value;
        } else {
           int64_t value = *ms.rbegin() + (int64_t)(p + 1) * s;
           ans = max(ans, value);
           save = max(value, save);
           ms.erase(ms.find(saved[k]));
        }
    }

    cout << ans << '\n';
}

int main() {
    int t = 1;
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    //cin >> t;
    for(int i = 1; i <= t; ++i) solve(i);
    return 0;
}


