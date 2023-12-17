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

const int N = 1e3 + 10;

int pre[N][N], a[N][N], n, m, v[N];
ii sp[10][N];

ii query(int l, int r) {
	int k = 31 - __builtin_clz(r - l + 1);
	return min(sp[k][l], sp[k][r - (1 << k) + 1]);
}

i64 f(int n) {
	return n * (n + 1ll) / 2;
}

i64 count(int n, int lo, int hi, int last) {
	if(lo > hi) return 0;
	ii ans = query(lo, hi);
	if(ans.first == last) return count(n, lo, ans.second - 1, last) + count(n, ans.second + 1, hi, last);
	int x = 0;
	if(lo > 0) x = max(x, v[lo - 1]);
	if(hi < n - 1) x = max(x, v[hi + 1]);
	return (ans.first - x) * f(hi - lo + 1ll) + count(n, lo, hi, ans.first);
}

i64 count(int n) {
	for(int i = 0; i < n; ++i) sp[0][i] = {v[i], i};
	int lg = 32 - __builtin_clz(n);
	for(int i = 1; i < lg; ++i)
	for(int j = 0; j + (1 << i) <= n; ++j)
		sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);	
	return count(n, 0, n - 1, 0);
}

void solve() {
	i64 ans = 0;

	cin >> n >> m;

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			pre[i][j] = 1;
			cin >> a[i][j];
			if(a[i][j] == a[i][j - 1]) pre[i][j] += pre[i][j - 1];
		}
	}

	for(int j = 1; j <= m; ++j) {
		int lo = 1, k = 0;
		for(int i = 1; i <= n; ++i) {
			if(a[i][j] == a[lo][j]) v[k++] = pre[i][j];
			else {
				lo = i;
				ans += count(k);
				v[0] = pre[i][j];
				k = 1;
			}
		}
		ans += count(k);
	}

	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
