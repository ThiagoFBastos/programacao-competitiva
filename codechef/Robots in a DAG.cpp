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

const int N = 101, inf = 1e7;

struct FlowEdge {
    int v, u, cap, flow = 0;
    FlowEdge(int v, int u, int cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0, s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, int cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].emplace_back(m);
        adj[u].emplace_back(m + 1);
        m += 2;
    }

    bool bfs() {
    	fill(level.begin(), level.end(), -1);    
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for(int id : adj[v]) {
                if(edges[id].cap - edges[id].flow < 1 || level[edges[id].u] != -1) continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int pushed) {
        if(!pushed || v == t) return pushed;
        for(int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if(level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;
            int tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if(tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
    
   int flow() {
        int f = 0;
        while(bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed = dfs(s, inf)) f += pushed;
        }
        return f;
    }
};

int path[N][N];

void solve() {
	
	int n, m, k;

	cin >> n >> m >> k;

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		path[i][j] = 0;

	vector<vector<ii>> g(n);

	while(m--) {
		int u, v;
		cin >> u >> v;
		g[u - 1].emplace_back(v - 1, 1);
	}

	for(auto& v : g) {
		sort(v.begin(), v.end());
		for(int i = 1; i < (int)v.size(); ++i) 
			if(v[i].first == v[i - 1].first) v[i].second = 1 + v[i - 1].second;
		v.resize(unique(v.begin(), v.end()) - v.begin());
	}

	path[0][0] = 1;
	for(int i = 1; i < n; ++i) {
		for(int u = 0; u < n; ++u) {
			if(!path[i - 1][u]) continue;
			for(ii v : g[u]) path[i][v.first] = 1;
		}
	}

	int lo = 1, hi = n + 1;
	bool ok = false;

	while(lo < hi) {
		int mid = (lo + hi) / 2;

		Dinic d(n * mid + 1, 0, n * mid);

		for(int i = 1; i < mid; ++i) {
			for(int u = 0; u < n; ++u) {
				if(!path[i - 1][u]) continue;
				for(ii v : g[u]) d.add_edge((i - 1) * n + u, i * n + v.first, v.second);
			}
			if(path[i][n - 1]) d.add_edge(i * n + n - 1, mid * n, inf);
		}

		if(d.flow() >= k) {hi = mid; ok = true;}
		else lo = mid + 1;
	}

	if(!ok) hi = 0;

	cout << hi - 1 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}