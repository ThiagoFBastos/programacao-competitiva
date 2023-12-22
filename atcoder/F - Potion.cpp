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

const int N = 101, inf = 1e9 + 100;

int dp[N][N];

void solve() {

	int n;
	i64 target;
	
	cin >> n >> target;
	
	vector<int> a(n);
	
	for(int& v : a) cin >> v;
	
	i64 ans = LLONG_MAX;
	
	for(int m = 1; m <= n; ++m) {
	
		for(int i = 0; i <= m; ++i)
		for(int j = 0; j < m; ++j)
			dp[i][j] = -inf;
			
		dp[0][0] = 0;
		
		for(int i = 0; i < n; ++i) {
			int x = a[i] % m, sz = min(i, m);
			for(int k = sz; k >= 0; --k) {
				for(int j = 0; j < m; ++j) {
					int y = x + j;
					if(y >= m) y -= m;
					dp[k + 1][y] = max(dp[k + 1][y], dp[k][j] + a[i]);
				}
			}
		}

		int val = dp[m][target % m];
		if(val >= 0) ans = min(ans, (target - val) / m);
	}
	
	cout << ans << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
   // cin >> t;
    while(t--) solve();
    return 0;
}
