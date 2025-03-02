#include "bits/stdc++.h"

using namespace std;

const int N = 1e6 + 10, MOD = 1e9 + 7;

int lz[4 * N], a[N];
pair<int, int> st[4 * N][2];

void build(int a[N], int l, int r, int p = 1) {
    lz[p] = 0;
    
    if(l == r) {
        st[p][0] = {a[l], -l};
        st[p][1] = {MOD - a[l], -l};
        return;
    }

    int m = (l + r) / 2;

    build(a, l, m, 2 * p);
    build(a, m + 1, r, 2 * p + 1);

    st[p][0] = max(st[2 * p][0], st[2 * p + 1][0]);
    st[p][1] = max(st[2 * p][1], st[2 * p + 1][1]);
}

void propagate(int p) {
    if(!lz[p]) return;
    swap(st[2 * p][0], st[2 * p][1]);
    swap(st[2 * p + 1][0], st[2 * p + 1][1]);
    lz[2 * p] ^= 1;
    lz[2 * p + 1] ^= 1;
    lz[p] = 0;
}

void upd(int l, int r, int lo, int hi, int p = 1) {
    if(l > r || r < lo || l > hi) return;
    else if(lo >= l && hi <= r) {
        swap(st[p][0], st[p][1]);
        lz[p] ^= 1;
        return;
    }

    int m = (lo + hi) / 2;

    propagate(p);

    upd(l, r, lo, m, 2 * p);
    upd(l, r, m + 1, hi, 2 * p + 1);
    
    st[p][0] = max(st[2 * p][0], st[2 * p + 1][0]);
    st[p][1] = max(st[2 * p][1], st[2 * p + 1][1]);
}

void solve(int test) {
    int n, q; 
    int64_t ans = 0;

    cin >> n;

    for(int i = 0; i < n; ++i) cin >> a[i];

    build(a, 0, n - 1);

    cin >> q;

    while(q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        upd(l, r, 0, n - 1);
        auto [_, pos] = st[1][0];
        ans += -pos + 1;
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

