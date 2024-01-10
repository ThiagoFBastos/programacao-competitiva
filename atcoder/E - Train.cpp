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

using T = tuple<int, int, int>;
using C = pair<i64, int>;

void solve() {
	int n, m, x, y;
	
	cin >> n >> m >> x >> y;
	
	--x, --y;
	
	vector<vector<T>> g(n);
	vector<i64> cost(n, -1);
	priority_queue<C> pq;
	
	for(int i = 0; i < m; ++i) {
		int a, b, t, k;
		cin >> a >> b >> t >> k;
		--a, --b;
		g[a].emplace_back(b, t, k);
		g[b].emplace_back(a, t, k);
	}
	
	pq.emplace(0LL, x);
	
	while(!pq.empty()) {
		auto [tms, x] = pq.top();
		pq.pop();
		tms = -tms;
		if(cost[x] != -1) continue;
		cost[x] = tms;
		if(x == y) break;
		for(auto [y, t, k] : g[x]) {
			if(cost[y] != -1) continue;
			pq.emplace(-(tms + (k - tms % k) % k + t), y);
		}
	}
	
	cout << cost[y] << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
   // cin >> t;
    while(t--) solve();
    return 0;
}
