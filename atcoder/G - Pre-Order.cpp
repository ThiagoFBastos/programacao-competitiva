#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 500;
const int MOD = 998244353;

int dp1[MAXN][MAXN], dp2[MAXN][MAXN];

void solve() {
	
	int n;

	cin >> n;

	vector<int> p(n);

	for(int& v : p) cin >> v;

	for(int i = 0; i < n; ++i) dp1[i][i] = dp2[i][i] = 1;

	for(int L = 2; L <= n; ++L) {
		for(int i = 0; i + L <= n; ++i) {
			int j = i + L - 1;
			dp1[i][j] = dp2[i + 1][j];
			for(int k = i; k < j; ++k) {
			  if(p[i] < p[k + 1]) {
				  i64 X = (dp2[i][j] + (i64)dp1[i][k] * dp2[k + 1][j]) % MOD;
				  dp2[i][j] = X;
			  }
			}
			dp2[i][j] = (dp2[i][j] + dp1[i][j]) % MOD;
		}
	}

	cout << dp1[0][n - 1] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

