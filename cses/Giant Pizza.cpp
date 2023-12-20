#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
const int MAXN = 2e5;
vi G[MAXN], G_scc[MAXN];
int n, m, scc[MAXN], low[MAXN], p[MAXN], topo[MAXN], k = 0, t_scc = 0, t = 0;
bool seen[MAXN];
stack<int> S;
void dfs(int v) {
	low[v] = p[v] = t++;
	S.push(v);
	for(int u : G[v]) {
		if(p[u] == -1) {
			dfs(u);
			low[v] = min(low[v], low[u]);
		}
		else if(scc[u] == -1) 
			low[v] = min(low[v], p[u]);
	}
	if(p[v] == low[v]) {
		while(S.top() != v) {
			scc[S.top()] = t_scc;
			S.pop();
		}
		scc[S.top()] = t_scc++;
		S.pop();
	}
}
void toposort(int v) {
	seen[v] = true;
	for(int u : G_scc[v])
		if(!seen[u]) toposort(u);
	topo[v] = k++;
}
bool solve(string& out) {
	for(int v = 2 * n - 1; v >= 0; --v) {
		p[v] = scc[v] = -1;
		seen[v] = false;
	} 
	for(int v = 2 * n - 1; v >= 0; --v)
		if(p[v] == -1) dfs(v);
	for(int v = 0 ; v < n; ++v)
		if(scc[v] == scc[v + n]) return false;
	for(int v = 2 * n - 1; v >= 0; --v)
		for(int u : G[v])
			if(scc[u] != scc[v])
				G_scc[scc[v]].push_back(scc[u]);
	for(int v = 0; v < t_scc; ++v)
		if(!seen[v]) toposort(v);
	for(int v = 0; v < t_scc; ++v) seen[v] = false;
	for(int v = 0; v < n; ++v) {
		if(topo[scc[v]] > topo[scc[v + n]]) out += '-';
		else out += '+';
		out += ' ';
	}
	return true;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> m >> n;
	for(int i = 0; i < m; ++i) {
		int t1, t2;
		char s1, s2;
		cin >> s1 >> t1 >> s2 >> t2;
		--t1, --t2;
		if(s1 == '-') t1 += n;
		if(s2 == '-') t2 += n;
		G[t1 < n ? t1 + n : t1 - n].push_back(t2);
		G[t2 < n ? t2 + n : t2 - n].push_back(t1);
	}
	string out;
	if(solve(out)) cout << out << '\n';
	else cout << "IMPOSSIBLE\n";
	return 0;
}
