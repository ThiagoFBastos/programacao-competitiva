#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 1e3;
const int MAXM = 2e5 + 100;
const int INF = 1e9 + 100;

template<int MAXN, int MAXM>
struct dinic {
	int n, ned, first[MAXN], work[MAXN];
	int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

	dinic() {}

	dinic(int n) : n {n} {
		memset(first, -1, sizeof(int) * (n+1));
		ned = 0;
	}

	void add(int u, int v, int c) {
		to[ned] = v, cap[ned] = c;
		nxt[ned] = first[u];
		first[u] = ned++;
		to[ned] = u, cap[ned] = 0;
		nxt[ned] = first[v];
		first[v] = ned++;
	}

	int dfs(int u, int f, int s, int t) {
		if(!f || u == t) return f;
		for(int& e = work[u]; e != -1; e = nxt[e]) {
			int v = to[e];
			if(dist[v] == dist[u] + 1 && cap[e] > 0) {
				int df = dfs(v, min(f, cap[e]), s, t);
				if(df > 0) {
					cap[e] -= df;
					cap[e ^ 1] += df;
					return df;
				}
			}
		}
		return 0;
	}

	bool bfs(int s, int t) {
		memset(dist, -1, sizeof(int) * (n+1));
		dist[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int e = first[u]; e != -1; e = nxt[e]) {
				int v = to[e];
				if(dist[v] < 0 && cap[e] > 0) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
			}
		}
		return dist[t] >= 0;
	}

	i64 maxflow(int s, int t) {
		i64 res = 0;
		while(bfs(s, t)) {
			memcpy(work, first, sizeof(int) * (n+1));
			while(int f = dfs(s, INF, s, t))
				res += f;
		}
		return res;
	}
};

dinic<MAXN, MAXM> flow;

void solve() {
	int n, m;

	cin >> n >> m;

	if(n + m == 0) exit(0);

	vector<int> voto(n);
	vector<vector<int>> g(n + 1);

	for(int& v : voto) cin >> v;	
	voto.insert(voto.begin(), 0);

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;	
		g[u].push_back(v);
		g[v].push_back(u);
	}

	flow = dinic<MAXN, MAXM>(n + 2);

	for(int i = 1; i <= n; ++i) {
		if(voto[i]) flow.add(i, n + 2, 1);
		else flow.add(n + 1, i, 1);
		for(int j : g[i]) flow.add(i, j, 1);
	}

	cout << flow.maxflow(n + 1, n + 2) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
	return 0;
}