#pragma GCC optimize("O3", "Ofast")
#pragma GCC target("mmx","sse","sse2")
#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 1;
int SQRT[450][2 * N + 1], skip[500], p[N], pre[N];
int chunk_sz, chunks, n;
void create() {
    ++n;
    chunk_sz = sqrt(n);
    chunks = (n + chunk_sz - 1) / chunk_sz;
    for(int i = 0; i < n; ++i) ++SQRT[i / chunk_sz][pre[i]];
}
int query(int k, int x, int y) {
    int cnt = 0, L = k / chunk_sz, R = chunks - 1;
    int f = min(n, (L + 1) * chunk_sz);
    for(int i = k; i < f; ++i) {
        cnt += pre[i] + skip[L] == x;
        --SQRT[L][pre[i]];
        ++SQRT[L][pre[i] + y];
        pre[i] += y;    
    }
    if(L != R) {
        for(int i = R * chunk_sz; i < n; ++i) {
            cnt += pre[i] + skip[R] == x;
            --SQRT[R][pre[i]];
            ++SQRT[R][pre[i] + y];
            pre[i] += y;
        }
    }
    for(++L; L < R; ++L) {
        if(x >= skip[L]) cnt += SQRT[L][x - skip[L]];
        skip[L] += y;
    }
    return cnt;
}
void solve() {
    cin >> n;
    pre[0] = 0;
    for(int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        p[a] = i;
        pre[i] = pre[i - 1] - 1;
    }
    for(int i = 0; i <= n; ++i) pre[i] += n;
    create();
    auto ans = 0LL;
    for(int i = n - 1; i; --i) {
        int L = p[i];
        ans += query(L, pre[L] + skip[L / chunk_sz], 2);
    }
    cout << ans << '\n';
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}