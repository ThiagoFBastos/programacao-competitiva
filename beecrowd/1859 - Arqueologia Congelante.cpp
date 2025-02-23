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

const int N = 51, M = 1e4 + 100;
const i64 MOD[2] = {i64(1e9 + 7), (1ll << 31) - 1};
const i64 BASE[2] = {5507, 9501659};

i64 pot[2][M];
int adj[N][N];

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

vector<i64> get_hash(string& s, i64 MOD, i64 BASE) {
	int n = s.size();
	vector<i64> h(n + 1);
	i64 b = 1;
	h[0] = 0;
	for(int i = 1; i <= n; ++i) {
		b = b * BASE % MOD;
		h[i] = (h[i - 1] + b * (s[i - 1] - 'A' + 1)) % MOD;
	}
	return h;
}

void solve() {
	int n, p;
	
	cin >> n >> p;	

	for(int k = 0; k < 2; ++k) {
		pot[k][0] = 1;
		for(int i = 1; i < M; ++i) pot[k][i] = pot[k][i - 1] * BASE[k] % MOD[k];
	}

	map<pair<i64, i64>, set<int>> hashes;
	
	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		int m = s.size();
		int l = (p * m + 99) / 100;
		s += s;
		auto my_hash_1 = get_hash(s, MOD[0], BASE[0]);
		auto my_hash_2 = get_hash(s, MOD[1], BASE[1]);
		for(int j = 0; j < m; ++j) {
			i64 X = my_hash_1[j + l] - my_hash_1[j];
			i64 Y = my_hash_2[j + l] - my_hash_2[j];
			if(X < 0) X += MOD[0];	
			if(Y < 0) Y += MOD[1];
			X = X * pot[0][m - j - 1] % MOD[0];
			Y = Y * pot[1][m - j - 1] % MOD[1];
			auto& h = hashes[make_pair(X, Y)];
			for(int k : h) adj[k][i] = 1;
			h.insert(i);
		}
	}
	
	int ans = inf;
	for(int i = 1; i < n; ++i) {
		Dinic d(n + 2, n, n + 1);
		for(int u = 0; u < n; ++u) {
			d.add_edge(n, u, !u ? inf : 0);
			d.add_edge(u, n + 1, u == i ? inf : 0);
			for(int v = u + 1; v < n; ++v) {
				if(!adj[u][v]) continue;
				d.add_edge(u, v, adj[u][v]);
				d.add_edge(v, u, adj[u][v]);
			}
		}
		ans = min(ans, d.flow());
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
