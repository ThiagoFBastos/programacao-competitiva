#include "bits/stdc++.h"
using namespace std;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	vector<double> e(n, 0), re(n, 0), rp(n, 0), p(n, 0);
	double ans;
	
	for(int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		g[x - 1].push_back(y - 1);
	}
	
	p[0] = 1;
	
	for(int v = 0; v < n; ++v) {
		int k = size(g[v]);
		for(int u : g[v]) {
			e[u] += (p[v] + e[v]) / k;
			p[u] += p[v] / k;
		}
	}

	ans = e[n - 1];
	
	rp[n - 1] = 1;
	
	for(int v = n - 1; v >= 0; --v) {
		int k = size(g[v]);
		for(int u : g[v]) {
			re[v] += (re[u] + rp[u]) / k;
			rp[v] += rp[u] / k;
		}
		if(k == 1) continue;
		auto E = 0.0;
		auto EF = 0.0;
		for(int u : g[v]) {
			EF += e[v] * rp[u] / k + re[u] * p[v] / k + p[v] * rp[u] / k;
			E += e[v] * rp[u] / (k - 1) + re[u] * p[v] / (k - 1) + p[v] * rp[u] / (k - 1);
		}
		for(int u : g[v]) {
			auto x = e[v] * rp[u] / (k - 1) + re[u] * p[v] / (k - 1) + p[v] * rp[u] / (k - 1);
			auto y = e[n - 1] - EF + E - x;
			if(y > 0) ans = min(ans, y);
		}
	}
	cout << fixed << setprecision(9) << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
