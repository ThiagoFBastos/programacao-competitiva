#include "bits/stdc++.h"
using namespace std;
int n, m;
int matching(vector<vector<pair<int, int>>>& G) {
	int edges = 0, n = G.size(), ans = 0;
	for(int i = 0; i < n; ++i) edges += G[i].size();
	edges >>= 1;
	vector<bool> emp(edges, false), free(n, true);
	vector<int> first(n);
	vector<pair<int, int>> pai(n);
	while(true) {
		queue<pair<int, int>> q;
		bool quit = true;
		fill(first.begin(), first.end(), -1);
		for(int k = 0; k < n / 2; ++k) {
			if(!free[k]) continue;
			first[k] = k;
			pai[k] = {k, -1};
			q.push({k, 0});
		}
		while(!q.empty()) {
			auto [v, t] = q.front();
			q.pop();
			int u = first[v];
			if(!free[u]) continue;
			else if(t && free[v]) {
				quit = false;
				++ans;
				free[u] = free[v] = false;
				for(int w = v; w != pai[w].first; w = pai[w].first, t ^= 1) emp[pai[w].second] = t;
			} else {
				for(auto [w, e] : G[v]) {
					if(first[w] != -1 || emp[e] != t) continue;
					pai[w] = {v, e};
					first[w] = u;
					q.push({w, t ^ 1});
				}
			}
		}
		if(quit) break;
	}
	return ans;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(cin >> n >> m) {
		vector<vector<int>> D(n);
		vector<vector<pair<int, int>>> G(2 * n);
		int e = 0;
		for(int i = 0; i < m; ++i) {
			int x, y;
			cin >> x >> y;
			--x, --y;
			D[x].push_back(y);
		}
		for(int k = 0; k < n; ++k) {
			for(int u : D[k]) {
				G[k].push_back({u + n, e});
				G[u + n].push_back({k, e++});
			}
		}
		cout << n - matching(G) << '\n';
	}
	return 0;
}