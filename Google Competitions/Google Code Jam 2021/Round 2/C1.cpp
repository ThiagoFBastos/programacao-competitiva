#include "bits/stdc++.h"
using namespace std;
using ii = pair<int, int>;
const int maxn = 1e5 + 1, mod = 1e9 + 7;
int caso, n;
long long fat[maxn], inv[maxn], invfat[maxn];
auto C(int n, int k) {
	return fat[n] * invfat[n - k] % mod * invfat[k] % mod;
}
struct sparse_table {
	vector<vector<ii>> sp;
	sparse_table() {}
	sparse_table(vector<int>& a) {
		int n = size(a);
		int m = 32 - __builtin_clz(n);
		sp = vector<vector<ii>>(m, vector<ii>(n));
		for(int i = 0; i < n; ++i) sp[0][i] = {a[i], -i};
		for(int i = 1; i < m; ++i)
		for(int j = 0; j + (1 << i) - 1 < n; ++j)
			sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << i - 1)]);
	}
	ii query(int l, int r) {
		int m = 31 - __builtin_clz(r - l + 1);
		return min(sp[m][l], sp[m][r - (1 << m) + 1]);
	}
};
sparse_table sp;
vector<int> v;
long long solve(int L, int R, int k) {
	if(L > R) return 1;
	else if(L == R) return v[L] == k;
	auto [x, y] = sp.query(L, R);
	if(x != k) return 0;
	y = -y;
	return C(R - L, y - L) * solve(L, y - 1, k) % mod * solve(y + 1, R, k + 1) % mod;
}
void solve() {
	int n;
	cin >> n;
	v.resize(n);
	for(int i = 0; i < n; ++i) cin >> v[i];
	sp = sparse_table(v);
	cout << "Case #" << caso << ": " << (solve(0, n - 1, 1) + mod) % mod << '\n'; 
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invfat[i] = 1;
	for(int i = 2; i < maxn; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = -(mod / i) * inv[mod % i] % mod;
		invfat[i] = invfat[i - 1] * inv[i] % mod;
	}
	int t;
	cin >> t;
	for(caso = 1; caso <= t; ++caso) solve();
	return 0;
}