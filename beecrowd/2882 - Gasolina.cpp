#include "bits/stdc++.h"
using namespace std;

const int inf = 1e9;

struct FlowEdge {
    int v, u, cap, flow = 0, weight;
    FlowEdge(int v, int u, int cap, int weight) : v(v), u(u), cap(cap), weight(weight){}
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

    void add_edge(int v, int u, int cap, int weight) {
        edges.emplace_back(v, u, cap, weight);
        edges.emplace_back(u, v, 0, weight);
        adj[v].emplace_back(m);
        adj[u].emplace_back(m + 1);
        m += 2;
    }

    bool bfs(int max_time) {
    	fill(level.begin(), level.end(), -1);    
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for(int id : adj[v]) {
            	auto [_, u, cap, flow, weight] = edges[id];
                if(cap - flow < 1 || weight > max_time || level[u] != -1) continue;
                level[u] = level[v] + 1;
                q.push(u);
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int pushed, int max_time) {
        if(!pushed || v == t) return pushed;
        for(int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            auto [_, u, cap, flow, weight] = edges[id];
            if(level[v] + 1 != level[u] || weight > max_time || cap - flow < 1) continue;
            int tr = dfs(u, min(pushed, cap - flow), max_time);
            if(tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
    
   int flow(int max_time) {
        int f = 0;
        for(auto& e : edges) e.flow = 0;
        while(bfs(max_time)) {
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed = dfs(s, inf, max_time)) f += pushed;
        }
        return f;
    }
};

void solve() {
	int P, R, C;
	
	cin >> P >> R >> C;
	
	Dinic G(P + R + 2, P + R, P + R + 1);
	
	int demanda = 0;
	
	for(int i = 0; i < P; ++i) {
		int dem;
		cin >> dem;
		demanda += dem;
		G.add_edge(R + i, P + R + 1, dem, 0);
	}
	
	for(int i = 0; i < R; ++i) {
		int estoque;
		cin >> estoque;
		G.add_edge(P + R, i, estoque, 0);
	}
	
	int lo = inf, hi = 0;
	
	while(C--) {
		int p, r, t;
		cin >> p >> r >> t;
		--p, --r;
		lo = min(lo, t);
		hi = max(hi, t);
		G.add_edge(r, p + R, inf, t);
	}

	int max_time = hi++;

	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(G.flow(mid) == demanda) hi = mid;
		else lo = mid + 1;
	}
	
	if(hi > max_time) cout << "-1\n";
	else cout << hi << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
