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
 
const int N = 100010;
 
i64 dp[N];
 
void solve() {
	int n, m;
 
	cin >> n;
 
	vector<tuple<int, int, int, int>> a;
	int s = 0;
	
	for(int i = 0; i < n; ++i) {
		int c, f, v;
		cin >> c >> f >> v;
		a.pb({f, 1, c, v});
	}
 
	cin >> m;
 
	for(int i = n; i < n + m; ++i) {
		int c, f, v;
		cin >> c >> f >> v;
		a.pb({f, 0, c, v});
	}
 
	sort(rall(a));
 
	fill(dp, dp + N, -INFLL);
	dp[0] = 0;
 
	for(int i = 0; i < n + m; ++i) {
		auto [f, t, c, v] = a[i];	
		if(t == 1) {
			for(int j = s; j >= 0; --j) dp[j + c] = max(dp[j + c], dp[j] - v);
			s += c;
		} else {
			for(int j = c; j <= s; ++j) dp[j - c] = max(dp[j - c], dp[j] + v);
		}
	}
 
	for(int j = s; j; --j) dp[j - 1] = max(dp[j - 1], dp[j]);
 
	cout << dp[0] << '\n'; 
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
