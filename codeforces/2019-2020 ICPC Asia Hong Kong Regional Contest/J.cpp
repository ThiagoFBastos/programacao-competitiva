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

const int N = 64, MOD = 1e9 + 7;

array<array<i64, N>, N> dp[2];

int f(string& s, int m) {
   
   int n = s.size();
   
   for(int i = 0; i < m; ++i)
   for(int j = 0; j < m; ++j)
     dp[0][i][j] = 0;
     
    dp[0][0][0] = 1;
    
    int sum = 0, f = 0, mod = 0;
    
    vector<int> P(n + 1);
    
    P[0] = 1;
    for(int i = 1; i <= n; ++i) P[i] = 10ll * P[i - 1] % m;
    
    for(int k = 0; k < n; ++k) {
      int X = s[k] - '0', B = P[n - k - 1];
      
      for(int i = 0; i < m; ++i)
      for(int j = 0; j < m; ++j)
        dp[1][i][j] = 0;
      
      for(int d = 0; d <= 9; ++d) {
         for(int i = 0; i < m; ++i) {
           for(int j = 0; j < m; ++j) {
             int k = ((d % m * i + j - B * d) % m + m) % m;
             dp[1][(i + d) % m][k] = (dp[1][(i + d) % m][k] + dp[0][i][j]) % MOD;
           }
         }
         
         if(d > X) {
             int Y = (((f + d * sum - mod - d * B) % m) + m) % m;
             dp[1][(sum + d) % m][Y] = (dp[1][(sum + d) % m][Y] + MOD - 1) % MOD;
         }
      }
       
      f = (f + X * sum) % m;
      sum = (sum + X) % m;
	  mod = (mod + B * X) % m;
      
      swap(dp[0], dp[1]);
    }

    int cnt = 0;
    
    for(int i = 0; i < m; ++i) cnt = (cnt + dp[0][i][0]) % MOD;
      
    return cnt;
}

int g(string& L, int m) {
    int f = 0, n = L.size(), sum = 0, mod = 0;
    for(char ch : L) {
      f = (f + sum * (ch - '0')) % m;
      sum = (sum + ch - '0') % m;
      mod = (10 * mod + ch - '0') % m;
    }
    return f == mod;
}

void solve() {
   string L, R;
   int m;

   cin >> L >> R >> m;

   int cnt = f(R, m) - f(L, m) + g(L, m);
   cout << (cnt + MOD) % MOD << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}

