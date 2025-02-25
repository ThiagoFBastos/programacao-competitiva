#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 1e4 + 100;

int sz[N], head[N], pos[N], par[N], depth[N], weight[N], st[2 * N];

struct hld {
	int n, tms;

	void updSeg(int k, int x) {
		k += n;
		st[k] = x;
		for(k /= 2; k; k /= 2) st[k] = max(st[2 * k], st[2 * k + 1]);
	}

	int querySeg(int l, int r) {
		int ans = 0;
		for(l += n, r += n; l <= r; l /= 2, r /= 2) {
			if(l & 1) ans = max(ans, st[l++]);
			if(~r & 1) ans = max(ans, st[r--]);
		}
		return ans;
	}

	int queryPath(int a, int b) {
		int ans = 0;
		while(head[a] != head[b]) {
			if(depth[head[a]] > depth[head[b]]) swap(a, b);
			ans = max(ans, querySeg(pos[head[b]], pos[b]));
			b = par[head[b]];
		}
		if(depth[a] > depth[b]) swap(a, b);
		return max(ans, querySeg(pos[a] + 1, pos[b]));
	}

	void updNode(int a, int b, int x) {
		updSeg(pos[depth[a] > depth[b] ? a : b], x);	
	}

	void dfs(vector<vector<ii>>& adj, int u, int p) {
		sz[u] = 1, par[u] = p;
		if(!adj[u].empty() && adj[u][0].first == p) swap(adj[u].back(), adj[u].front());
		for(auto& e : adj[u]) {
			int& v = e.first, w = e.second;
			if(v == p) continue;
			weight[v] = w;
			depth[v] = 1 + depth[u];
			dfs(adj, v, u);
			sz[u] += sz[v];
			if(sz[v] > sz[adj[u][0].first]) swap(v, adj[u][0].first);
		}
	}

	void get_paths(vector<vector<ii>>& adj, int u, int p) {
		pos[u] = tms++;
		for(auto& e : adj[u]) {
			int& v = e.first, w = e.second;
			if(v == p) continue;
			else if(2 * sz[v] >= sz[u]) head[v] = head[u];
			get_paths(adj, v, u);
		}
	}
		
	hld(vector<vector<ii>>& adj) {
		n = adj.size();
	
		memset(st, 0, sizeof(int) * (2*n+1));
	
		tms = 0;

		for(int i = 0; i < n; ++i) head[i] = i;

		depth[0] = 0;

		dfs(adj, 0, 0);
		get_paths(adj, 0, 0);

		for(int i = 0; i < n; ++i) st[pos[i] + n] = weight[i];
		for(int i = n - 1; i > 0; --i) st[i] = max(st[2 * i], st[2 * i + 1]);
	}
};

void solve() {
	int n;
	cin >> n;
	vector<vector<ii>> adj(n);
	vector<ii> edge(n);
	for(int i = 1; i < n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		edge[i - 1] = {a, b};
		adj[a].emplace_back(b, c);
		adj[b].emplace_back(a, c);
	}
	hld data(adj);
	while(true) {
		string t;
		cin >> t;
		if(t == "DONE") break;
		else if(t == "QUERY") {
			int a, b;
			cin >> a >> b;
			cout << data.queryPath(a - 1, b - 1) << '\n';
		} else {
			int i, ti;
			cin >> i >> ti;
			--i;
			data.updNode(edge[i].first, edge[i].second, ti);
		}
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}