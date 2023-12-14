#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
int n, m, w[MAXN], k = 0;
vector<int> G[MAXN];
bool vis[MAXN];
void dfs(int v) {
	++w[k];
	vis[v] = true;
	for(int u : G[v]) if(!vis[u]) dfs(u);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	memset(vis, 0, n * sizeof(bool));
	memset(w, 0, n * sizeof(int));
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;	
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i = 0; i < n; ++i) if(!vis[i]) dfs(i), ++k;
	bitset<MAXN + 1> S;
	S[0] = 1;
	for(int i = 0; i < k; ++i) S |= S << w[i];
	for(int i = 1; i <= n; ++i) cout << S[i];
	cout << '\n';
	return 0;
}
