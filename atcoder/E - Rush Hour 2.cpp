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

void solve() {	
	
	int n, m;

	cin >> n >> m;

	vector<vector<tuple<int, int, int>>> g(n);
	vector<i64> t(n, -1);
	priority_queue<pair<i64, int>> pq;

	while(m--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		--a, --b;
		g[a].emplace_back(b, c, d);
		g[b].emplace_back(a, c, d);
	}

	pq.emplace(0LL, 0);

	while(!pq.empty()) {
		auto [cst, v] = pq.top();
		pq.pop();
		cst *= -1;
		if(t[v] != -1) continue;
		t[v] = cst;
		for(auto [u, c, d] : g[v]) {
			if(t[u] != -1) continue;

			i64 lo = cst, hi = 1e9 + 100;

			if(lo <= hi) {
				while(lo < hi) {
					i64 mid = (lo + hi) / 2;
					i64 X = d * (2ll + mid);
					i64 Y = (2 + mid + d) * (1ll + mid);
					if(X < Y) hi = mid;
					else lo = mid + 1;
				}
			} else hi = cst;

			pq.emplace(-(hi + 1ll * c + d / (1ll + hi)), u); 
		}
	}

	if(t.back() == -1) {
		cout << "-1\n";
		return;
	}

	cout << t.back() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

