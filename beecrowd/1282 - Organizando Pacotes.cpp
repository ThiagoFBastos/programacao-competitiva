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

const i64 inf = 1e15L + 100;

double intersc(i64 a0, i64 b0, i64 a1, i64 b1) {
	return (b1 - b0) / double(a0 - a1);
}

void solve() {
/*
	dp[i] = min W(X[i] - X[j]) + dp[j] 
	dp[i] = min (preW[i] - preW[j]) * X[i] - (preWX[i] - preWX[j]) + dp[j]
	dp[i] = -preWX[i] + preW[i] * X[i] + min - preW[j] * X[i] + preWX[j] + dp[j]
*/

	int n, k;
	
	cin >> n >> k;
	
	if(cin.eof()) exit(0);
	
	vector<i64> preW(n + 1, 0), preWX(n + 1, 0), dp[2];
	vector<int> x(n + 1), w(n + 1);	
	
	for(int i = 1; i <= n; ++i) {
		cin >> x[i] >> w[i];
		preW[i] = preW[i - 1] + w[i];
		preWX[i] = preWX[i - 1] + (i64)w[i] * x[i];
	}
	
	for(int i = 0; i < 2; ++i) dp[i].assign(n + 1, inf);
	
	dp[0][0] = 0;
	
	for(int i = 1; i <= k; ++i) {
		vector<pair<i64, i64>> st(n + 1);
		int lo = 0, hi = 1;
		st[0] = make_pair(-preW[i - 1], preWX[i - 1] + dp[0][i - 1]);
		for(int j = i; j <= n; ++j) {
			i64 a0 = -preW[j], b0 = preWX[j] + dp[0][j];
			while(lo + 1 < hi) {
				auto [a0, b0] = st[lo];
				auto [a1, b1] = st[lo + 1];
				if(a0 * x[j] + b0 < a1 * x[j] + b1) break;
				++lo;
			}
			auto [a, b] = st[lo];
			dp[1][j] = x[j] * a + b - preWX[j] + preW[j] * x[j];
			while(lo + 1 < hi) {
				auto [a1, b1] = st[hi - 1];
				auto [a2, b2] = st[hi - 2];
				if(intersc(a0, b0, a1, b1) > intersc(a1, b1, a2, b2)) break;
				--hi;
			}
			st[hi++] = make_pair(a0, b0);
		}
		swap(dp[0], dp[1]);
	}
	
	cout << dp[0][n] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}