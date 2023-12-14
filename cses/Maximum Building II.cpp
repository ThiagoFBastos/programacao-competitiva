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
 
const int N = 1e3 + 10, K = 10;
 
i64 sum[N][N], frq[N][N];
int suf[N], n, m;
ii sp[K][N];
 
ii query(int l, int r) {
	int k = 31 - __builtin_clz(r - l + 1);
	return min(sp[k][l], sp[k][r - (1 << k) + 1]);
}
 
void rec(int l, int r, int wmin) {	
	if(l > r) return;
 
	int wmax = query(l, r).fi, n = r - l + 1;
	
	sum[1][wmin] += n + 1;
	sum[n + 1][wmin] -= n + 1;
	sum[1][wmax + 1] -= n + 1;
	sum[n + 1][wmax + 1] += n + 1;
 
	++frq[1][wmin];
	--frq[n + 1][wmin];
	--frq[1][wmax + 1];
	++frq[n + 1][wmax + 1];
	
	while(l <= r) {
		auto [x, k] = query(l, r);
		if(x == wmax) {
			rec(l, k - 1, wmax + 1);
			l = k + 1;
		} else {
			rec(l, r, wmax + 1);
			break;
		}
	}
}
 
void solve() {
	cin >> n >> m;
 
	vector<string> g(n);
 
	for(auto& l : g) cin >> l;
 
	for(int j = m - 1; j >= 0; --j) {
 
		for(int i = 0; i < n; ++i) {
			suf[i] = g[i][j] == '.' ? 1 + suf[i] : 0;
			sp[0][i] = {suf[i], i};
		}
 
		for(int k = 1; (1 << k) <= n; ++k)
			for(int j = 0; j + (1 << k) <= n; ++j)
				sp[k][j] = min(sp[k - 1][j], sp[k - 1][j + (1 << (k - 1))]);
 
		rec(0, n - 1, 1);
	}
 
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
			frq[i][j] += frq[i - 1][j] + frq[i][j - 1] - frq[i - 1][j - 1];
			cout << sum[i][j] - i * frq[i][j] << ' ';
		}
		cout << '\n';
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
