#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
vector<int> G[MAXN];
int low[MAXN], t[MAXN], scc[MAXN], t_scc = 0, t_in = 0;
stack<int> S;
void dfs(int v) {
	low[v] = t[v] = t_in++;
	S.push(v);
	for(int u : G[v]){
		if(t[u] == -1){
			dfs(u);
			low[v] = min(low[v], low[u]);
		}
		else if(scc[u] == -1) low[v] = min(low[v], t[u]);
	}
	if(t[v] == low[v]){
		while(S.top() != v){
			scc[S.top()] = t_scc;
			S.pop();
		}	
		scc[S.top()] = t_scc++;
		S.pop();
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for(int v = 0; v < n; ++v) t[v] = scc[v] = -1;
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v);
	}
	for(int v = 0; v < n; ++v) {
		if(t[v] == -1) dfs(v);
		for(int u : G[v]){
			if(scc[v] == scc[u]) {
				queue<int> Q;
				vector<int> p(n, -1);
				p[u] = u;
				Q.push(u);
				while(!Q.empty()) {
					int w = Q.front();
					Q.pop();
					if(w == v) break;
					for(int x : G[w]) if(p[x] == -1) {p[x] = w; Q.push(x);}
				}
				stack<int> res;
				while(true) {
					res.push(v);
					if(v == u) break;
					v = p[v];
				}
				cout << 1 + res.size() << '\n';
				while(!res.empty()) {cout << res.top() + 1 << ' '; res.pop();}
				cout << u + 1 << '\n';
				return 0;
			}
		}
	}
	cout << "IMPOSSIBLE\n";
	return 0;
}
