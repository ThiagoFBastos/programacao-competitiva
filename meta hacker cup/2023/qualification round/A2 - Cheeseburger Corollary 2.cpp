#include "bits/stdc++.h"

using namespace std;

int kase = 1;

void solve() {
    int64_t A, B, C;

    cin >> A >> B >> C;

    int64_t lo = 1, hi = 1e18L;

    cout << "Case #" << kase++ << ": ";

    while(lo < hi) {
        int64_t mid = (lo + hi) / 2, cost = LLONG_MAX;

        cost = min((__int128)cost, (__int128)mid * A);
        cost = min((__int128)cost, (__int128)(mid + 2) / 2 * B);

        int64_t b = mid - (mid + 2) / 2;
        int64_t a = (mid + 2) / 2 - b;

        if(a >= 0 && b >= 0) cost = min((__int128)cost, (__int128)a * A + (__int128)b * B);

        if(cost > C) hi = mid;
        else lo = mid + 1;
    }

    cout << hi - 1 << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin >> t;

    while(t--) solve();

    return 0;
}

