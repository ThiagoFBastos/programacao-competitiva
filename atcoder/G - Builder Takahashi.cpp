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

const i64 inf = 1e16L;

struct FlowEdge {
    int v, u;
	i64 cap, flow = 0;
    FlowEdge(int v, int u, i64 cap) : v(v), u(u), cap(cap) {}
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

    void add_edge(int v, int u, i64 cap) {
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

    i64 dfs(int v, i64 pushed) {
        if(!pushed || v == t) return pushed;
        for(int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if(level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;
            i64 tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if(tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
    
   i64 flow() {
        i64 f = 0;
        while(bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while(i64 pushed = dfs(s, inf)) f += pushed;
        }
        return f;
    }

	vector<int> S() {
		vector<bool> vis(n, false);
		vector<int> ans;
		queue<int> q;
		q.push(s);
		vis[s] = true;
		 while (!q.empty()) {
            int v = q.front();
            q.pop();
            for(int id : adj[v]) {
                if(edges[id].cap - edges[id].flow < 1 || vis[edges[id].u]) continue;
                vis[edges[id].u] = true;
                q.push(edges[id].u);
            }
        }
		for(int u = 0; u < n; ++u) {
			if(!vis[u]) continue;
			for(int id : adj[u]) {
				int v = edges[id].u;
				if(!vis[v] && edges[id].cap) ans.push_back(u / 2 + 1);
			}
		}
		return ans;
	}
};

void solve() {
	int n, m;
	cin >> n >> m;
	
	Dinic g(2 * n, 0, 2 * (n - 1) + 1);

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g.add_edge(2 * a + 1, 2 * b, inf);
		g.add_edge(2 * b + 1, 2 * a, inf);
	}

	for(int i = 0; i < n; ++i) {
		int c;
		cin >> c;
		g.add_edge(2 * i, 2 * i + 1, !c ? inf : c);
	}

	cout << g.flow() << '\n';
	auto v = g.S();
	sort(v.begin(), v.end());	
	v.resize(unique(v.begin(), v.end()) - v.begin());
	cout << v.size() << '\n';
	for(int k : v) cout << k << ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
