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

const int N = 1e3 + 100, M = 1e7 + 1e3 + 100, MOD = 1e9 + 7;

int fat[M];
int bit[N][N], cnt[N][N];
int n, m;

void upd(int i, int j, int v) {
	for(int x = i; x <= n; x += x & -x)
	for(int y = j; y <= m; y += y & -y)
		bit[x][y] += v;
}

int query(int i, int j) {
	int ans = 0;
	for(int x = i; x > 0; x -= x & -x)
	for(int y = j; y > 0; y -= y & -y)
		ans += bit[x][y];
	return ans;
}

int query(int i0, int j0, int i1, int j1) {
	return query(i1, j1) - query(i1, j0 - 1) - query(i0 - 1, j1) + query(i0 - 1, j0 - 1);
}

i64 exp(i64 n, int p) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % MOD;
		n = n * n % MOD;
	}
	return ans;
}

int C(int n, int k) {
	return exp((i64)fat[k] * fat[n - k] % MOD, MOD - 2) * fat[n] % MOD;
}

void solve() {
	int dia = 1; 
	cin >> n >> m;
	cin.ignore();
	for(string s; getline(cin, s);) {
		int x0, y0, x1, y1, c, b;
		if(sscanf(s.c_str(), "%d%d%d%d%d", &x0, &y0, &x1, &y1, &c) == 5)
			cout << "Day #" << dia++ << ": " << C(query(x0, y0, x1, y1) + c - 1, c) << '\n';
		else if(sscanf(s.c_str(), "%d%d%d", &x0, &y0, &b) == 3) {
			upd(x0, y0, b);
			cnt[x0][y0] += b;
		} else {
			sscanf(s.c_str(), "%d%d", &x0, &y0);
			upd(x0, y0, -cnt[x0][y0]);
			cnt[x0][y0] = 0;
		}
	}
}

int main() {	
	fat[0] = 1;
	for(int i = 1; i < M; ++i) fat[i] = 1ll * fat[i - 1] * i % MOD;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}