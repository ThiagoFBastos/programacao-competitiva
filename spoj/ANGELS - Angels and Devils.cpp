#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int INF = 1e9;

struct dinic {
	vector<int> first, work, to, nxt, dist, flow;
	int n, ned;

	dinic() {}

	dinic(int n) : n {n} {
		work.resize(n+1);
		dist.resize(n+1);
		first.assign(n+1,-1);
		ned = 0;
	}

	void add(int u, int v, int c) {
		for(int i=0;i<2;++i){
			to.emplace_back();
			flow.emplace_back();
			nxt.emplace_back();
		}
		to[ned] = v, flow[ned] = c;
		nxt[ned] = first[u];
		first[u] = ned++;
		to[ned] = u, flow[ned] = 0;
		nxt[ned] = first[v];
		first[v] = ned++;
	}

	int dfs(int u, int f, int s, int t) {
		if(!f || u == t) return f;
		for(int& e = work[u]; e != -1; e = nxt[e]) {
			int v = to[e];
			if(dist[v] == dist[u] + 1 && flow[e] > 0) {
				int df = dfs(v, min(f, flow[e]), s, t);
				if(df > 0) {
					flow[e] -= df;
					flow[e ^ 1] += df;
					return df;
				}
			}
		}
		return 0;
	}

	bool bfs(int s, int t) {
		fill(dist.begin(), dist.end(), -1);
		dist[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int e = first[u]; e != -1; e = nxt[e]) {
				int v = to[e];
				if(dist[v] < 0 && flow[e] > 0) {
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
			copy(first.begin(), first.end(), work.begin());
			while(i64 f = dfs(s, INF, s, t))
				res += f;
		}
		return res;
	}
};

const int N = 310;

int r[N][N], c[N][N];
char g[N][N];

void solve() {
	int n, m, id = 0;
	cin >> n >> m;	

	vector<ii> ed;

	for(int i = 0; i < n; ++i) {
		int last = m;
		for(int j = 0; j < m; ++j) {
			cin >> g[i][j];
			if(g[i][j] == 'A') {
				if(j - last > 0) ++id, last = m;
			} else if(g[i][j] == 'H') last = j;
			r[i][j] = id+1;
		}
		++id;
	}

	int rows = id;

	for(int j = 0; j < m; ++j) {
		int last = n;
		for(int i = 0; i < n; ++i) {
			c[i][j] = id+1;
			if(g[i][j] == 'A') {
				if(i - last > 0) ++id, last = i;
			} else if(g[i][j] == 'H') {
				last = i;
				ed.emplace_back(r[i][j], c[i][j]);
			}
		}
		++id;
	}

	int cols = id - rows;

	dinic flow(id + 2);

	vector<bool> vis(id+1,false);

	for(auto& e : ed) {
		int r = e.first, c = e.second;
		flow.add(r, c, 1);
		vis[r] = vis[c] = true;
	}
	
	for(int i = 1; i <= rows; ++i) if(vis[i]) flow.add(id + 1, i, 1);
	for(int i = rows+1; i <= id; ++i) if(vis[i]) flow.add(i, id + 2, 1);

	cout << flow.maxflow(id + 1, id + 2) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}