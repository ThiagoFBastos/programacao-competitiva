#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 5e3 + 100, MOD = 1e9 + 7;

i64 fat[N], inv[N], invf[N], dp[N];

i64 C(int n, int k) {
    return fat[n] * invf[n - k] % MOD * invf[k] % MOD;
}

i64 exp(i64 n, int p) {
    i64 ans = 1;
    for(; p > 0; p >>= 1) {
        if(p & 1) ans = ans * n % MOD;
        n = n * n % MOD;
    }
    return ans;
}

void solve() {
   int n, m, k;
   
   cin >> n >> m >> k;
   
   for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
   
   for(int i = 2; i < N; ++i) {
       fat[i] = i * fat[i - 1] % MOD;
       inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
       invf[i] = inv[i] * invf[i - 1] % MOD;
   }
      
    for(int i = 1; i <= k; ++i) {
        
        dp[i] = exp(i, n) % MOD;
                
        for(int j = i - 1; j; --j)
            dp[i] = (dp[i] - dp[j] * C(i, j)) % MOD;
            
        dp[i] = (MOD + dp[i]) % MOD;
    }
   
   cout << dp[k] * C(m, k) % MOD << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}


