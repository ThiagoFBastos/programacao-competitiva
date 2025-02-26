#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int N = 2600, MOD = 1e9 + 7;

i64 fat[N], inv[N], invf[N];

i64 C(int n, int k) {
    return fat[n] * invf[k] % MOD * invf[n - k] % MOD;
}

void solve() {
    int n, m, k, x = INT_MAX;
    cin >> n;

    vector<int> a(n + 1);
    vector<bool> sep(n + 1, false);

    int p = 0, q = 0;

    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        q += a[i];
    }   

    cin >> m;

    while(m--) {
        int c;  
        cin >> c;
        sep[c] = true;
        p += a[c];
    }

    cin >> k;
    vector<int> l(k);

    if(!k) x = 0;

    for(int& y : l) {
        cin >> y;
        x = min(x, a[y]);
    }
    
    q += (1 - k) * x - p;
    for(int y : l) a[y] -= x;

    for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
    for(int i = 2; i < N; ++i) {
        fat[i] = fat[i - 1] * i % MOD;
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        invf[i] = invf[i - 1] * inv[i] % MOD;
    }

    if(p > q + 1) {
        cout << "0\n";
        return;
    } 
    
    i64 P = fat[p];
    i64 Q = fat[q];

    for(int i = 1; i <= n; ++i) {
        if(!sep[i]) continue;
        P *= invf[a[i]];
        P %= MOD;
    }

    Q = Q * invf[x] % MOD;

    for(int i = 1; i <= n; ++i) if(!sep[i]) Q = Q * invf[a[i]] % MOD;

    cout << P * Q % MOD * C(q + 1, p) % MOD << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}