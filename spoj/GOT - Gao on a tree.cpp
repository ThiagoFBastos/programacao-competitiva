#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 1e5 + 100;

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
		return max(ans, querySeg(pos[a], pos[b]));
	}

	void updNode(int a, int x) {
		updSeg(pos[a], x);	
	}

	void dfs(vector<vector<int>>& adj, int u, int p) {
		sz[u] = 1, par[u] = p;
		if(!adj[u].empty() && adj[u][0] == p) swap(adj[u].back(), adj[u].front());
		for(int& v : adj[u]) {
			if(v == p) continue;
			depth[v] = 1 + depth[u];
			dfs(adj, v, u);
			sz[u] += sz[v];
			if(sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
		}
	}

	void get_paths(vector<vector<int>>& adj, int u, int p) {
		pos[u] = tms++;
		for(int v : adj[u]) {
			if(v == p) continue;
			else if(2 * sz[v] >= sz[u]) head[v] = head[u];
			get_paths(adj, v, u);
		}
	}
		
	hld(vector<vector<int>>& adj) {
		n = adj.size();
		memset(st, 0, sizeof(int) * (2*n+1));
		tms = 0;
		for(int i = 0; i < n; ++i) head[i] = i;
		dfs(adj, 0, 0);
		get_paths(adj, 0, 0);
	}
};

using QUERY = tuple<int, int, int>;

void solve() {
	int n, m;
	cin >> n >> m;

	if(cin.eof()) exit(0);

	map<int, vector<int>> S;
	map<int, vector<QUERY>> query;
	vector<vector<int>> adj(n);
	vector<bool> ans(m,false);

	for(int i = 0; i < n; ++i) {
		int c;
		cin >> c;
		S[c].push_back(i);
	}

	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;			
		query[c].emplace_back(a-1, b-1, i);
	}

	hld data(adj);
	int flag = 1;

	for(auto& X : S) {
		int c = X.first;
		auto& v = X.second;

		for(int u : v) data.updNode(u, flag);
			
		auto it = query.find(c);
		
		if(it != query.end()) {
			for(auto& Y : it->second) {
				int a, b, pos;
				tie(a, b, pos) = Y;
				ans[pos] = data.queryPath(a, b) == flag;
			}
		}

		++flag;
	}

	for(bool v : ans) cout << (v ? "Find\n" : "NotFind\n");
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = -1;
	//cin >> t;
	while(1) solve();
	return 0;
}