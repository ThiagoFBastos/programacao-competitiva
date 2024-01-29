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

const int N = 512, INF = 1e9;

int d[N][N];

void solve() {
	int n, m, q;

	cin >> n >> m >> q;

	vector<vector<ii>> g(n);

	while(m--) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		g[u].emplace_back(v, w);
	}

	
	vector<int> ans(q);
	vector<vector<tuple<int, int, int>>> Q(n);

	for(int i = 0; i < q; ++i) {
		int u, v, x;
		cin >> u >> v >> x;
		--u, --v;
		Q[u].emplace_back(v, i, x);
	}

	for(int i = 0; i < n; ++i) {
		for(int k = 1; k <= n; ++k)
		for(int u = 0; u < n; ++u)
			d[k][u] = INF;

		d[1][i] = 0;

		for(int k = 1; k < n; ++k)
			for(int u = 0; u < n; ++u)
				for(auto [v, w] : g[u])
					d[k + 1][v] = min(d[k + 1][v], d[k][u] + w);
		
		for(auto [v, pos, x] : Q[i]) {
			int val = INF;
			for(int j = 1; j <= n; ++j) val = min(val, d[j][v] + j * x);
			ans[pos] = val == INF ? -1 : val;
		}
	}

	for(int v : ans) cout << v << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

