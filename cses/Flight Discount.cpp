#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100000
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	vii G[MAXN];
	ll cost[MAXN][2];
	int n, m;
	cin >> n >> m;
	for(int v = 0; v < n; ++v)
		cost[v][0] = cost[v][1] = -1;
	for(int k = 0; k < m; ++k) {
		int u, v, cuv;
		cin >> u >> v >> cuv;
		G[u - 1].push_back({v - 1, cuv});
	}
	set<tuple<ll, int, int>> pq;
	pq.insert(make_tuple(0, 0, 0));
	while(!pq.empty()) {
		auto [c, u, cp_use] = *pq.begin();
		pq.erase(pq.begin());
		if(cost[u][cp_use] == -1) {
			cost[u][cp_use] = c;
			if(u == n - 1 && cp_use) break;
			if(cp_use) {
				for(auto [v, dv] : G[u]) {
					if(cost[v][1] == -1)
						pq.insert(make_tuple(dv + c, v, 1));
				}
			}
			else {
				for(auto [v, dv] : G[u]) {
					if(cost[v][1] == -1)
						pq.insert(make_tuple((dv >> 1) + c, v, 1));
					if(cost[v][0] == -1)
						pq.insert(make_tuple(dv + c, v, 0));
				}
			}
		}
	}
	cout << cost[n - 1][1] << '\n';
	return 0;
}
