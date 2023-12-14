#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
 
const int N = 5e3 + 10, MOD = 1e9 + 7;
 
int fat[2 * N], inv[2 * N], invf[2 * N], dp[2][N];
int frq[26];
 
void preprocess(int n) {
    for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
    for(int i = 2; i <= n; ++i) {
        fat[i] = (i64)i * fat[i - 1] % MOD;
        inv[i] = (MOD - MOD / i + 0ll) * inv[MOD % i] % MOD;
        invf[i] = (i64)inv[i] * invf[i - 1] % MOD;
    }
}
 
int C(int n, int k) {
    return (i64)fat[n] * invf[k] % MOD * invf[n - k] % MOD;
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
 
    string s;
    
    cin >> s;
 
    int n = size(s), tot = 0;
    for(char c : s) ++frq[c - 'a'];
 
    if(2 * *max_element(frq, frq + 26) - 1 > n) {
        cout << "0\n";
        return 0;
    }
    
    preprocess(2 * n);
 
    dp[0][0] = 1;
 
    for(int c = 0; c < 26; ++c) {
        if(!frq[c]) continue;
 
        memset(dp[1], 0, sizeof dp[1]);
 
        for(int i = 0; i <= tot; ++i) {
            for(int j = 1; j <= frq[c]; ++j) {
                i64 groups = (i64)fat[frq[c]] * C(frq[c] - 1, j - 1) % MOD;
                i64 merges = C(i + j, j);
                i64 ways = ((frq[c] - j) % 2 ? -1ll : 1ll) * dp[0][i] * groups % MOD * merges % MOD;
                dp[1][i + j] = (dp[1][i + j] + ways) % MOD;
            }
        }
 
        tot += frq[c];
 
        memcpy(dp[0], dp[1], sizeof dp[1]);
    }
 
    int ans = 0;
    for(int i = 0; i <= n; ++i) {
        ans += dp[0][i];
        ans %= MOD;
    }
 
    for(int i = 0; i < 26; ++i) ans = (i64)ans * invf[frq[i]] % MOD;
 
    cout << (ans+MOD)%MOD << '\n';
 
    return 0;
}
