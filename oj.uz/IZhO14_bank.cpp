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
 
int s[1 << 20];
 
array<bool, (1 << 20)> dp[2];
 
void solve() {
	int n, m;
 
	cin >> n >> m;
 
	vector<int> a(n + 1, 0), b(m);
 
	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i] += a[i - 1];
	}
 
	for(int& v : b) cin >> v;
 
	for(int i = 1; i < (1 << m); ++i) {
		s[i] = s[i ^ (i & -i)] + b[__builtin_ctz(i)];
		dp[0][i] = s[i] == a[n];
	}
 
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < (1 << m); ++j) dp[1][j] = false;
		for(int j = (1 << m) - 1; j >= 0; --j) {
			bool flag = dp[0][j] || dp[1][j];
			for(int S = j; S; S -= S & -S) dp[1][j ^ (S & -S)] = dp[1][j ^ (S & -S)] || flag;			
			dp[1][j] = dp[1][j] && s[j] == a[n] - a[i];
		}
		swap(dp[0], dp[1]);
	}
 
	cout << (dp[0][0] ? "YES\n" : "NO\n");
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
