#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
const int MAXN = 2e4;
int C, P, low[MAXN], pre[MAXN], scc[MAXN], t_in, scc_pos;
stack<int> S;
void dfs(vvi& G, int v) {
	low[v] = pre[v] = t_in++;
	S.push(v);
	for(int u : G[v]) {
		if(pre[u] == -1) {
			dfs(G, u);
			low[v] = min(low[u], low[v]);
		}
		else if(scc[u] == -1) low[v] = min(low[v], pre[u]);
	}
	if(low[v] == pre[v]) {
		while(S.top() != v) {
			scc[S.top()] = scc_pos;
			S.pop();
		}
		scc[S.top()] = scc_pos++;
		S.pop();
	}
}
bool solve(vvi& G) {
	for(int v = 0; v < 2 * P; ++v)
		pre[v] = scc[v] = -1;
	scc_pos = t_in = 0;
	for(int v = 0; v < 2 * P; ++v)
		if(pre[v] == -1) dfs(G, v);
	for(int v = 0; v < P; ++v)
		if(scc[v] == scc[v + P]) return false;
	return true;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true) {
		cin >> C >> P;
		if(C == 0 && P == 0) break;
		vvi G(2 * P);
		for(int k = 0; k < C; ++k) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			if(a || b) {
				if(a && b) G[a + P - 1].push_back(b - 1), G[b + P - 1].push_back(a - 1);
				else if(b) G[b + P - 1].push_back(b - 1);
				else G[a + P - 1].push_back(a - 1);
			}
			if(c || d) {
				if(c && d) G[c - 1].push_back(d + P - 1), G[d - 1].push_back(c + P - 1);
				else if(c) G[c - 1].push_back(c + P - 1);
				else G[d - 1].push_back(d + P - 1);
			}
		}
		if(solve(G)) cout << "yes\n";
		else cout << "no\n";
	}
	return 0;
}