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
 
const int inf = 1e9, N = 2e3 + 100;
 
int n, p, q;
array<int, N> dp[2];
 
vector<int> a;
 
bool f(int w) {
	for(int i = 0; i <= n; ++i) dp[0][i] = -inf;
	dp[0][0] = 0;
	for(int i = 1; i <= p + q; ++i) {
		int hi[2] = {0};
		for(int i = 0; i <= n; ++i) dp[1][i] = -inf;
		for(int k = 0; k < n; ++k) {
			while(hi[0] < n && a[hi[0]] - a[k] < w) ++hi[0];
			while(hi[1] < n && a[hi[1]] - a[k] < 2 * w) ++hi[1];
			dp[1][hi[0]] = max(dp[1][hi[0]], dp[0][k] + 1);
			dp[1][hi[1]] = max(dp[1][hi[1]], dp[0][k]);
		}
		swap(dp[0], dp[1]);
		if(dp[0][n] >= p || i - dp[0][n] <= q) return true;
	}
	return false;
}
 
void solve() {
 
	cin >> n >> p >> q;
 
	a.resize(n);
 
	for(int i = 0; i < n; ++i) cin >> a[i];
 
	if(p + q >= n) {
		cout << "1\n";
		return;
	}
 
	sort(a.begin(), a.end());
 
	vector<int> d;
 
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			d.push_back(a[j] - a[i] + 1);
			d.push_back((a[j] - a[i] + 2) / 2);
		}
	}
 
	sort(d.begin(), d.end());
	d.resize(unique(d.begin(), d.end()) - d.begin());
 
	int lo = 0, hi = (int)d.size() - 1;
 
	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(f(d[mid])) hi = mid;
		else lo = mid + 1;	
	}
 
	cout << d[hi] << '\n';
}		
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
