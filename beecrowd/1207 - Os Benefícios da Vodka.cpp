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

const int MAXN = 1500, MAXM = 5e5, INF = 1e7;

struct Dinic {
	int ned, first[MAXN], work[MAXN];
	int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];
	int n;

	Dinic(int n) : n {n}{
		memset(first, -1, sizeof(int) * n);
		ned = 0;
	}

	void add(int u, int v, int f) {
		to[ned] = v, cap[ned] = f;
		nxt[ned] = first[u];
		first[u] = ned++;
		to[ned] = u, cap[ned] = 0;
		nxt[ned] = first[v];
		first[v] = ned++;
	}

	int dfs(int u, int f , int s , int t) {
		if(u == t) return f ;
		int v , df;
		for(int& e = work[u] ; e != -1; e = nxt[e]) {
			v = to[e] ;
			if(dist[v] == dist[u] + 1 && cap[e] > 0) {
				df = dfs(v , min(f, cap[e]), s , t) ;
				if(df > 0) {
					cap[e] -= df ;
					cap[e ^ 1] += df ;
					return df;
				}
			}
		}
		return 0;
	}

	bool bfs(int s, int t) {
		int u, v ;
		memset(dist , -1, sizeof(int) * n) ;
		dist[s] = 0;
		queue<int> q ; q.push(s) ;
		while (!q.empty()) {
			u = q.front(); 
			q.pop() ;
			for(int e = first[u]; e != -1; e = nxt[e]) {
				v = to[e];
				if(dist[v] < 0 && cap[e] > 0 ) {
					dist[v] = dist[u] + 1;
					q.push(v) ;
				}
			}
		}
		return dist[t] >= 0;
	}

	int dinic(int s, int t) {
		int result = 0, f;
		while(bfs(s, t)) {
			memcpy(work, first, sizeof(int) * n) ;
			while(f = dfs(s, INF, s, t)) result += f;
		}
		return result;
	}
};


void solve() {
	int n, m;
	i64 ans = 0;
	cin >> n >> m;
	if(cin.eof()) exit(0);
	Dinic g(n + m + 2);
	vector<int> deg(m);
	for(int i = 0; i < n; ++i) {
		int p;
		cin >> p;
		g.add(i, n + m + 1, p);
	}
	for(int& v : deg) cin >> v;
	for(int i = 0; i < m; ++i) {
		int b;	
		cin >> b;
		ans += b;		
		g.add(n + m, n + i, b);
		for(int j = 0; j < deg[i]; ++j) {
			int id;
			cin >> id;
			g.add(n + i, id - 1, INF);
		}
	}
	cout << ans - g.dinic(n + m, n + m + 1) << '\n';
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//cin >> t;
	while(true) solve();
}