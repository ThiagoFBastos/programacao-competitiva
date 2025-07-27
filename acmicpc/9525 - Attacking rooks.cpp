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
	int n;

	cin >> n;

	vector<string> s(n);
	int m = n;

	for(auto& v : s) {
		cin >> v;
		m += count(all(v), 'X');
	}
	
	Dinic d(2 * m + 2, 2 * m, 2 * m + 1);
	vector<int> row(n), col(n);
	int cols = n, rows = n;

	for(int i = 0; i < n; ++i) {
		col[i] = row[i] = i;
		d.add_edge(2 * m, row[i], 1);
		d.add_edge(col[i] + m, 2 * m + 1, 1);
	}

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(s[i][j] == 'X') {
				d.add_edge(2 * m, rows, 1);
				d.add_edge(cols + m, 2 * m + 1, 1);
				row[i] = rows++;
				col[j] = cols++;
			} else
				d.add_edge(row[i], m + col[j], 1);
		}
	}

	cout << d.flow() << '\n';	
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	//cin >> t;
    while(t--) solve();
    return 0;
}

