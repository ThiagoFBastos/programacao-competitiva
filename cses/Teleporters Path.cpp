#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
int n, m, d_in[MAXN], d_out[MAXN];
vector<int> G[MAXN], path;
void dfs(int v) {
	while(!G[v].empty()) {
		int u = G[v].back();
		G[v].pop_back();
		dfs(u);	
	}
	path.push_back(v + 1);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	memset(d_in, 0, n * sizeof(int));
	memset(d_out, 0, n * sizeof(int));
	for(int k = 0; k < m; ++k) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		++d_out[u];
		++d_in[v];
		G[u].push_back(v);
	}
	if(!(d_in[0] + 1 == d_out[0] && d_out[n - 1] + 1 == d_in[n - 1])) {
		cout << "IMPOSSIBLE\n";
		return 0;
	}
	for(int v = 1; v < n - 1; ++v) {
		if(d_in[v] != d_out[v]) {
			cout << "IMPOSSIBLE\n";
			return 0;
		}
	}
	dfs(0);
	if(m + 1 != path.size()) 
		cout << "IMPOSSIBLE\n";
	else {
		reverse(path.begin(), path.end());
		for(int v : path) cout << v << ' ';
		cout << '\n';
	}
	return 0;
}
