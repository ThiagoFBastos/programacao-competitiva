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

const int N = 1e4 + 10, M = 1e5 + 10;

int n, m, c[N];
vector<ii> ed[M];
bool vis[M];

struct uf {
	vector<int> par, rank;
	stack<tuple<int, int, int, int>> st;
	
	uf() {}
	
	uf(int n) {
		par.resize(n);
		rank.assign(n, 0);
		iota(par.begin(), par.end(), 0);
	}
	
	int findSet(int v) {
		return v == par[v] ? v : findSet(par[v]);
	}
	
	bool join(int u, int v) {
		u = findSet(u);
		v = findSet(v);
		if(u == v) return false;
		else if(rank[u] > rank[v]) swap(u, v);
		st.emplace(u, v, rank[v], c[v]);
		par[u] = v;
		c[v] = gcd(c[v], c[u]);
		rank[v] += rank[u] == rank[v];
		return true;
	}
	
	bool rollback() {
		if(st.empty()) return false;
		int u, v, r, g;
		tie(u, v, r, g) = st.top();
		st.pop();
		c[v] = g;
		par[u] = u;
		rank[v] = r;
		return true;
	}
};

void solve() {
	int ans = 0;

	cin >> n >> m;

	for(int i = 0; i < n; ++i) {
		cin >> c[i];
		vis[c[i]] = true;
	}

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		ed[gcd(c[a], c[b])].pb({a, b});
	}

	uf dsu(n);

	for(int g = M - 1; g; --g) {
		bool ok = vis[g];
		for(int i = g; i < M; i += g) {
			for(auto [a, b] : ed[i]) {
				dsu.join(a, b);
				ok = ok || c[dsu.findSet(a)] == g;
			}
		}
		if(ok) ++ans;
		while(dsu.rollback());
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