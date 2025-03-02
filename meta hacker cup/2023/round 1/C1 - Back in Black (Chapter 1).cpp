#include "bits/stdc++.h"

using namespace std;

void solve(int test) {
    int n, q;
    string s;

    cin >> n >> s;

    vector<int> toggle(n + 1, 0), par(n + 1, 0);

    cin >> q;

    while(q--) {
        int x;
        cin >> x;
        par[x] ^= 1;
    }

    for(int p = 1; p <= n; ++p) {
        if(!par[p]) continue;
        for(int k = p; k <= n; k += p)
            toggle[k] ^= 1;
    }

    int ans = 0;

    for(int k = 1; k <= n; ++k) {
        if((toggle[k] ^ s[k - 1]) == '0') continue;
        ++ans;
        for(int i = k; i <= n; i += k) toggle[i] ^= 1;
    }

    cout << "Case #" << test << ": " << ans << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin >> t;

    for(int i = 1; i <= t; ++i) solve(i);

    return 0;
}

