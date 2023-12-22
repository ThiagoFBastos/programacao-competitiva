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

const int N = 50;
int win[N][N], pts[N], lost[N], id[N][N];

void solve() {
	int n, m;

	cin >> n >> m;

	while(m--) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		win[a][b] = 1;
		++pts[a], ++lost[b];
	}

	int t = n;

	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			id[i][j] = t++;

	for(int i = 0; i < n; ++i) {
		Dinic d(t + 2, t, t + 1);
		int flow = 0, p = n - 1 - lost[i];
		bool ok = true;
		for(int k = 0; k < n; ++k) {
			if(k == i) continue;
			if(p - 1 < pts[k]) {
				ok = false;
				break;
			}
			d.add_edge(k, t + 1, p - 1 - pts[k]);
			for(int j = k + 1; j < n; ++j) {
				if(i != j && win[k][j] + win[j][k] == 0) {
					++flow;
					d.add_edge(t, id[k][j], 1);
					d.add_edge(id[k][j], k, 1);
					d.add_edge(id[k][j], j, 1);
				}
			}
		}
		if(!ok) continue;
		if(flow == d.flow()) cout << i + 1 << ' ';
	}
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

