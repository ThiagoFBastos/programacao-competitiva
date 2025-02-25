#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int INF = 1e9 + 100;

struct dinic {
	int ned;
	vector<int> cap, nxt, first, to, work, dist;

	dinic(int n) {
		first.assign(n, -1);
		work.resize(n);
		dist.resize(n);
		ned = 0;
	}

	void add(int u, int v, int c) {
		to.emplace_back(v);
		cap.emplace_back(c);
		nxt.emplace_back(first[u]);
		first[u] = ned++;

		to.emplace_back(u);
		cap.emplace_back(0);
		nxt.emplace_back(first[v]);
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
		fill(dist.begin(), dist.end(), -1);
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
			copy(first.begin(), first.end(), work.begin());
			while(int f = dfs(s, INF, s, t))
				res += f;
		}
		return res;
	}
};

void solve() {
	int n, m;
	i64 ans = 0;
	cin >> n >> m;
	dinic d(2 * n + 2);
	for(int i = 0; i < n; ++i) {
		int p;	
		cin >> p;
		d.add(2 * n, 2 * i, INF);
		d.add(2 * i + 1, 2 * n + 1, 2 * p);
	}
	while(m--) {
		int a, b, w;
		cin >> a >> b >> w;
		--a, --b;

		d.add(2 * a, 2 * b + 1, w);
		d.add(2 * b + 1, 2 * a, w);

		d.add(2 * b, 2 * a + 1, w);
		d.add(2 * a + 1, 2 * b, w);
		
		d.add(2 * a, 2 * b, w);
		d.add(2 * b, 2 * a, w);

		d.add(2 * a + 1, 2 * b + 1, w);
		d.add(2 * b + 1, 2 * a + 1, w);

		ans += w;
	}
	cout << ans - d.maxflow(2 * n, 2 * n + 1) / 2 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
 