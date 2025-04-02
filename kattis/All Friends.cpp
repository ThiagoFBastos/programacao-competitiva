#include "bits/stdc++.h"
using namespace std;
int n, m, cnt = 0;
__uint128_t INF = 0, g[128];
bool backtracking(__uint128_t F, int k) {
    if(F == 0) {
        if(++cnt > 1000) return false;
        return true;
    } else if(k == n) return true;
    auto p = (__uint128_t)1 << k;
    if(p & F) {
        if(!backtracking(F & g[k], k + 1)) return false;
        __uint128_t S = F;
        for(int v = k + 1; v < n; ++v) {
            p = (__uint128_t)1 << v;
            if(p & F) S &= g[v];
        }
        return !S ? backtracking(F, k + 1) : true;
    }
    return backtracking(F, k + 1);
}
void solve() {
    cin >> n >> m;
    if(cin.eof()) exit(0);
    for(int v = 0; v < n; ++v) g[v] = 0;
    cnt = 0;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a] |= ((__uint128_t)1) << b;
        g[b] |= ((__uint128_t)1) << a;
    }
    if(!backtracking(INF, 0)) cout << "Too many maximal sets of friends.\n";
    else cout << cnt << '\n';
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    for(int k = 0; k < 128; ++k) INF |= (__uint128_t)1 << k;
    for(;;) solve();
    return 0;
}
