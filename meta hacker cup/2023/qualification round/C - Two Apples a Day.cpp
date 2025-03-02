#include "bits/stdc++.h"

using namespace std;

int kase = 1;

void solve() {
    int n;
    int64_t sum = 0;

    cin >> n;

    vector<int> a(2 * n - 1);

    for(int& v : a) {
        cin >> v;
        sum += v;
    }

    sort(a.begin(), a.end());
    
    cout << "Case #" << kase++ << ": ";

    if(n == 1) {
        cout << "1\n";
        return;
    }

    int64_t min_weight = LLONG_MAX;

    for(int k1 : {0, 1}) {
        for(int k2 : {0, 1}) {
            if(k1 + k2 == 2) continue;

            int lo = 0 + k1, hi = 2 * n - 2 - k2;
            int target = a[lo] + a[hi];
            int64_t want = 1ll * target * n - sum;

            if(want <= 0) continue;

            int64_t tmp = target - want;

            if(!binary_search(a.begin(), a.end(), tmp)) continue;

            while(lo < hi) {
                if(a[lo] == tmp) ++lo, tmp = -1;
                if(a[hi] == tmp) --hi, tmp = -1;
                if(lo == hi) break;
                if(a[lo] + a[hi] != target) {
                    want = -1;
                    break;
                } else
                    ++lo, --hi;
            }

            if(want != -1) min_weight = min(min_weight, want);
        }
    }

    if(min_weight == LLONG_MAX) cout << "-1\n";
    else cout << min_weight << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin >> t;

    while(t--) solve();

    return 0;
}

