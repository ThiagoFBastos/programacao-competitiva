#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int INF = 1e9;

void solve() {

	int n, m;
	
	cin >> n >> m;

	vector<vector<int>> g(n + 1);
	vector<int> dto(n + 1, INF), dfrom(n + 1, INF), amb;
	queue<int> q;

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		if(u && v) {
			g[u].push_back(v);
			g[v].push_back(u);
		} else amb.push_back(v);
	}

	dto[1] = 0;
	q.push(1);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int v : g[u]) {
			if(dto[v] != INF) continue;
			dto[v] = 1 + dto[u];
			q.push(v);
		}
	}

	dfrom[n] = 0;
	q.push(n);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int v : g[u]) {
			if(dfrom[v] != INF) continue;
			dfrom[v] = 1 + dfrom[u];
			q.push(v);
		}
	}

	int min_dist_to = INF, min_dist_from = INF, spec = INF;
	multiset<int> D;

	for(int v : amb) {
		min_dist_to = min(min_dist_to, dto[v]);
		min_dist_from = min(min_dist_from, dfrom[v]);
		D.insert(dfrom[v]);
	}

	if((int)size(amb) >= 2) {
		for(int v : amb) {
			D.erase(D.find(dfrom[v]));
			spec = min(spec, dto[v] + 2 + *D.begin());
			D.insert(dfrom[v]);
		}
	}
	
	for(int i = 1; i <= n; ++i) {
		int d = dto[n];
		d = min(d, min_dist_to + 1 + dfrom[i]);
		d = min(d, spec);
		d = min(d, min_dist_from + 1 + dto[i]);
		cout << (d == INF ? -1 : d) << ' ';
	}

	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
