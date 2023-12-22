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

const int mod = 998244353;

vector<vector<int>> g;
vector<int> c;
int n, d;

auto C() {
	vector<int> t(n, -1), deg(n);
	queue<int> q;
	for(int v = 0; v < n; ++v) {
		deg[v] = size(g[v]);
		if(deg[v] == 1) {
			t[v] = 0;
			q.push(v);
		}
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : g[u]) {
			if(--deg[v] != 1) continue;
			t[v] = 1 + t[u];
			q.push(v);
		}
	}
	int T = *max_element(t.begin(), t.end());
	vector<int> c;
	for(int v = 0; v < n; ++v) if(t[v] == T) c.push_back(v);
	d = 2 * T + (int)size(c) - 1;
	return c;
}

vector<int> a, b, h;

void preproc(int u, int p = -1) {
	a[u] = b[u] = 0;
	if(h[u] == d / 2) ++a[u];
	if(h[u] == (d + 1) / 2) ++b[u];
	for(int v : g[u]) {
		if(v == p) continue;
		h[v] = 1 + h[u];
		preproc(v, u);
		a[u] += a[v];
		b[u] += b[v];
	}
}

void solve() {
	cin >> n;
	
	g.resize(n);
	
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	if(n == 2) {
		cout << "1\n";
		return;
	}
	
	c = C();
	
	a.resize(n);
	b.resize(n);
	h.assign(n, 0);
	preproc(c[0]);
	i64 ans = 0;
	
	if(size(c) == 1) {
		i64 resto = 1;
		ans = 1;
		for(int v : g[c[0]]) {
			ans = ans * (a[v] + 1) % mod;
			resto = (resto + a[v]) % mod;
		}
		ans = (ans - resto) % mod;
	} else {
		i64 s = 0;
		for(int v : g[c[0]]) s = (s + a[v]) % mod;
		for(int v : g[c[0]]) {
			i64 k = (s - a[v]) % mod;
			ans = (ans + k * b[v]) % mod;
		}
	}
	
	cout << (ans + mod) % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
