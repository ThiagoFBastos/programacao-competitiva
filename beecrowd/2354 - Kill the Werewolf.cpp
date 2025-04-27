#include <bits/stdc++.h>

using namespace std;

const int inf = 1e7;

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

void solve() {
	int n, cnt {};
	cin >> n;
	
	vector<int> a[2];
	
	for(int i = 0; i < 2; ++i) a[i].resize(n);
	for(int i = 0; i < n; ++i) {
		cin >> a[0][i] >> a[1][i];
		--a[0][i], --a[1][i];
	}
	
	for(int i = 0; i < n; ++i) {
		int pts = 0;
		for(int j = 0; j < n; ++j) if(a[0][j] == i || a[1][j] == i) ++pts;
		
		Dinic dinic(2 * n + 2, 2 * n, 2 * n + 1);
		int m = 0;
		
		for(int j = 0; j < n; ++j) {
			dinic.add_edge(j + n, 2 * n + 1, max(pts - 1 - (j == a[0][i] || j == a[1][i]), 0));
			if(i == j || a[0][j] == i || a[1][j] == i) continue;
			++m;
			dinic.add_edge(2 * n, j, 1);
			dinic.add_edge(j, a[0][j] + n, 1);
			dinic.add_edge(j, a[1][j] + n, 1);
		}
		
		if(dinic.flow() != m) ++cnt;
	}
	
	cout << cnt << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	// cin >> t;
	while(t--) solve();
	return 0;
}