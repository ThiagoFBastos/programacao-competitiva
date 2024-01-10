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

const int MOD = 998244353, N = 2e3 + 100;

array<int, N> even[2], odd[2];

void solve() {
	int n, m, k, s, t, x;

	cin >> n >> m >> k >> s >> t >> x;

	--s, --t, --x;

	vector<vector<int>> adj(n);

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	even[0].fill(0);
	odd[0].fill(0);

	even[0][s] = 1;

	for(int i = 1; i <= k; ++i) {
		odd[1].fill(0);
		even[1].fill(0);
		for(int u = 0; u < n; ++u) {
			for(int v : adj[u]) {
				if(v == x) {
					even[1][v] += odd[0][u];
					odd[1][v] += even[0][u];
					if(even[1][v] >= MOD) even[1][v] -= MOD;
					if(odd[1][v] >= MOD) odd[1][v] -= MOD;
				} else {
					even[1][v] += even[0][u];
					odd[1][v] += odd[0][u];
					if(even[1][v] >= MOD) even[1][v] -= MOD;
					if(odd[1][v] >= MOD) odd[1][v] -= MOD;
				}
			}
		}
		swap(odd[0], odd[1]);
		swap(even[0], even[1]);
	}

	cout << even[0][t] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
