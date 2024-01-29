#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

using T = tuple<int, int, int>;

int n, m;
vector<vector<ii>> g;

vector<i64> dijkstra(int v) {
	priority_queue<pair<i64, int>> pq;
	vector<i64> cost(n, -1);
	pq.emplace(0LL, v);
	while(!pq.empty()) {
		auto [c, v] = pq.top();
		pq.pop();
		c = -c;
		if(cost[v] != -1) continue;
		cost[v] = c;
		for(auto [u, w] : g[v]) {
			if(cost[u] != -1) continue;
			pq.emplace(-c - w, u);
		}
	}
	return cost;
}

struct SegTree {
	vector<ordered_set<ii>> st;
	int n;
	
	SegTree(int n) {
		this->n = n;
		st.resize(2 * n + 1);
	}
	
	void upd(int k, ii x) {
		for(k += n; k > 0; k /= 2) st[k].insert(x);
	}
	
	int query(int l, int r, ii x) {
		int ans = 0;
		for(l += n, r += n; l <= r; l /= 2, r /= 2) {
			if(l & 1) ans += st[l++].order_of_key(x);
			if(~r & 1) ans += st[r--].order_of_key(x);
		}
		return ans;
	}
};

void solve() {
	
	cin >> n >> m;
	
	g.resize(n);
	
	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}
	
	vector<i64> c[3];
	vector<T> a(n);
	
	for(int i = 0; i < 3; ++i) {
		c[i] = dijkstra(i);
		auto p = c[i];
		sort(p.begin(), p.end());
		for(int j = 0; j < n; ++j) c[i][j] = lower_bound(p.begin(), p.end(), c[i][j]) - p.begin(); 
	}
	
	for(int i = 0; i < n; ++i) a[i] = {c[0][i], c[1][i], c[2][i]};
	
	sort(a.begin(), a.end());
	
	vector<ii> sweep(n);
	
	for(int i = 0; i < n; ++i) sweep[i] = {get<1>(a[i]), i};
	
	sort(sweep.begin(), sweep.end());
	
	SegTree st(n);
	int ans = 0;
	
	for(auto [_, i] : sweep) {
		auto [x, y, z] = a[i];
		int k = lower_bound(a.begin(), a.end(), a[i]) - a.begin();
		int cnt = st.query(0, k - 1, {z, i});
		st.upd(i, {z, i});
		ans += cnt == 0;
	}

	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


