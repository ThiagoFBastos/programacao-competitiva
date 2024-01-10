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

int n, q, tms;

vector<vector<int>> g, S;
vector<int> lo, hi, h;

void dfs(int u) {
	lo[u] = hi[u] = tms++;
	for(int v : g[u]) {
		h[v] = 1 + h[u];
		dfs(v);
		hi[u] = hi[v];
	}
}

void solve() {	
		
	cin >> n;

	g.resize(n);
	S.resize(n);
	lo.resize(n);
	hi.resize(n);
	h.assign(n, 0);

	for(int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		g[p - 1].push_back(i);
	}

	dfs(0);

	for(int i = 0; i < n; ++i) S[h[i]].push_back(lo[i]);
	for(auto& v : S) sort(v.begin(), v.end());

	cin >> q;
	
	while(q--) {
		int u, d;

		cin >> u >> d;

		--u;
		
		auto& v = S[d];

		int l = lower_bound(v.begin(), v.end(), lo[u]) - v.begin();
		int r = upper_bound(v.begin(), v.end(), hi[u]) - v.begin();

		cout << r - l << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

