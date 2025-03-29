#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
bitset<100000> seen;
int k, w, vis = 0, d1 = 0, d = 0;
void dfs(vvi& G, int v) {
	++vis;
	seen[v] = 1;
	if(G[v].size() > 2) ++d;
	else if(G[v].size() == 1) ++d1;
	for(int u : G[v]) if(!seen[u]) dfs(G, u);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true) {
		map<int, int> p;
		vvi G;
		int j = 0;
		cin >> k >> w;
		if(k == 0 && w == 0) break;
		for(int i = 0; i < w; ++i) {
			int a, b;
			cin >> a >> b;
			int u = p[a] - 1;
			int v = p[b] - 1;
			if(u == -1) u = j, p[a] = ++j, G.push_back({});
			if(v == -1) v = j, p[b] = ++j, G.push_back({});
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for(int v = 0; v < G.size(); ++v) {
			sort(G[v].begin(), G[v].end());
			auto it = unique(G[v].begin(), G[v].end());
			G[v].resize(it - G[v].begin());
		}
		bool flag = true;
		seen.reset();
		for(int v = 0; v < G.size(); ++v) {
			if(!seen[v]) {
				vis = 0, d1 = 0, d = 0;
				dfs(G, v);
				if(d || d1 == 0 && vis < k) {flag = false; break;}
			}
		}
		if(flag) cout << "Y\n";
		else cout << "N\n";
	}
	return 0;
}