#include "bits/stdc++.h"
using namespace std;
void solve() {
	int n, m, q;
	cin >> n >> m >> q;
	vector<int> p(n);
	vector<vector<int>> cc(n);
	vector<vector<pair<int, int>>> hs(n);
	for(int i = 0; i < n; ++i) {
		p[i] = i;
		cc[i].push_back(i);
		hs[i].push_back({i, 0});
	}
	for(int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		if(p[a] == p[b]) continue;
		int u = p[a], v = p[b];
		if(size(cc[u]) > size(cc[v])) swap(u, v);
		for(int w : cc[u]) {
			cc[v].push_back(w);
			hs[w].push_back({v, i});
			p[w] = v;
		}
	}
	while(q--) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		if(p[a] != p[b]) {
			cout << "-1\n";
			continue;
		}
		int i = int(size(hs[a])) - 1, j = int(size(hs[b])) - 1;
		for(int k = 31 - __builtin_clz(min(i, j) + 1); k >= 0; --k) {
			int I = i - (1 << k), J = j - (1 << k);
			if(I >= 0 && J >= 0 && hs[a][I].first == hs[b][J].first) i = I, j = J;
		}
		cout << max(hs[a][i].second, hs[b][j].second) << '\n';
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
 
