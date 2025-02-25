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
using i128 = __int128;

template<int MAXN>
struct HopcroftKarp {
	vector<int> adj[MAXN];
	int pv[MAXN], c[MAXN], dist[MAXN], n;
	
	HopcroftKarp() {}

	HopcroftKarp(int _n) {
		init(_n);
	}

	void init(int _n) {
		n = _n;
		memset(pv, 0, sizeof(int) * (n + 1));
		memset(c, -1, sizeof(int) * (n + 1));
		for(int i = 0; i <= n; ++i) adj[i].clear();
	}

	void add(int u, int v) {
		++u, ++v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	void color(int u, int p, int x) {
		if(c[u] != -1) return;
		c[u] = x;
		for(int v : adj[u]) color(v, u, x ^ 1);
	}

	bool bfs() {
		queue<int> q;
		for(int u = 1; u <= n; ++u) {
			if(!c[u] && !pv[u]) {
				dist[u] = 0;
				q.push(u);
			} else
				dist[u] = INF;
		}
		dist[0] = INF;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			if(dist[u] >= dist[0]) continue;
			for(int v : adj[u]) {
				if(dist[pv[v]] != INF) continue;
				dist[pv[v]] = 1 + dist[u];
				q.push(pv[v]);
			}
		}
		return dist[0] != INF;
	}

	bool dfs(int u) {
		if(!u) return true;
		for(int v : adj[u]) {
			if(dist[pv[v]] != dist[u] + 1) continue;
			if(!dfs(pv[v])) continue;
			pv[v] = u, pv[u] = v;
			return true;
		}
		dist[u] = INF;
		return false;
	}

	int maxMatching() {
		int res = 0;
		for(int i = 1; i <= n; ++i) color(i, -1, 0);
		while(bfs())
			for(int u = 1; u <= n; ++u)
				if(!c[u] && !pv[u] && dfs(u))
					++res;
		return res;
	}
};

const int N = 1e2 + 10, M = 10, K = 102410;

int hsh[1<<M];
HopcroftKarp<2 * K> hp;

int minPathCover(vector<ii>& e, int n) {
	hp.init(2 * n);
	for(auto [u, v] : e) hp.add(2 * u, 2 * v + 1);
	return n - hp.maxMatching();
}

void solve() {
	map<string, int> mp;
	map<array<int, M>, int> id;
	vector<ii> ed;
	int n;

	cin >> n;
	
	for(int i = 0; i < n; ++i) {
		int a[M], m;

		cin >> m;

		vector<string> s(m);
		for(auto& w : s) cin >> w;

		sort(all(s));

		for(int j = 0; j < m; ++j) {
			if(!mp.count(s[j])) mp[s[j]] = mp.size();
			a[j] = mp[s[j]];
		}

		for(int j = 1; j < (1 << m); ++j) {
			array<int, M> v;
			v.fill(-1);
			for(int k = 0, l = 0; k < m; ++k) {
				if(~j & (1 << k)) continue;
				v[l++] = a[k];
			}
			if(!id.count(v)) id[v] = id.size();
			hsh[j] = id[v];
			if(!(j & (j - 1))) continue;
			for(int k = 0; k < m; ++k) if(j & (1 << k)) ed.pb({hsh[j], hsh[j^(1<<k)]});
		}
	}

	cout << minPathCover(ed, id.size()) << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
