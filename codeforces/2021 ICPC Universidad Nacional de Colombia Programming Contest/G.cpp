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

const int N = 3e5 + 100;

template<class T>
struct BIT {
	vector<T> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};

vector<int> g[N];
int sp[19][N], depth[N], in[N], out[N], tms, n, q;

void dfs(int u, int p) {
	sp[0][u] = p;
	in[u] = tms++;
	for(int i = 1; (1 << i) <= n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(int v : g[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfs(v, u);
	}
	out[u] = tms;
}

int lca(int u, int v) {
	if(depth[u] > depth[v]) swap(u, v);
	int d = depth[v] - depth[u];
	for(int i = 0; (1 << i) <= d; ++i) if(d & (1 << i)) v = sp[i][v];
	if(u == v) return u;
	for(int i = 31 - __builtin_clz(depth[u]); i >= 0; --i) {
		if(sp[i][u] == sp[i][v]) continue;
		u = sp[i][u], v = sp[i][v];
	}
	return sp[0][u];
}

string toString(__int128 n) {
	string s;
	while(n > 0) {
		s += n % 10 + '0';
		n /= 10;
	}
	if(s.empty()) s = "0";
	reverse(s.begin(), s.end());
	return s;
}

void solve() {
	cin >> n;

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs(0, 0);

	BIT<__int128> cte(n), x1(n), x2(n);

	auto query = [&](int u) {
		__int128 X = cte.query(in[u]);
		__int128 Y = x1.query(in[u]);
		__int128 Z = x2.query(in[u]);
		return (X + (__int128)depth[u] * (Y + depth[u] * Z)) / 2;	
	};

	cin >> q;

	while(q--) {
		int t, u, v, k;
		cin >> t >> u >> v;
		--u;
		if(t == 0) {
			--v;
			int w = lca(u, v);
			__int128 ans = query(u) + query(v) - (w > 0) * query(sp[0][w]) - query(w);
			cout << toString(ans) << '\n';
		} else {
			cin >> k;

			__int128 X = -2ll * v * depth[u] + 2 * v + k * ((i64)depth[u] * depth[u] - depth[u]);
			__int128 Y = k + 2 * v - 2ll * k * depth[u];
			__int128 Z = k;
	
			cte.upd(in[u], X);
			cte.upd(out[u], -X);
			
			x1.upd(in[u], Y);
			x1.upd(out[u], -Y);

			x2.upd(in[u], Z);
			x2.upd(out[u], -Z);
		}
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

