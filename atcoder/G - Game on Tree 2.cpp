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

template<class T>
struct BIT {
	vector<T> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}

	int find_by_order(int k) {
		int i = 0, n = int(size(bit)) - 1;
		for(int j = 31 - __builtin_clz(n); j >= 0; --j) {
			int pos = i + (1 << j);
			if(pos > n || k - bit[pos] <= 0) continue;
			k -= bit[pos];
			i = pos;
		}
		return i + 1;
	}
};

const int INF = 2e9 + 100;

void solve() {
	int n;

	cin >> n;

	vector<vector<int>> g(n);
	vector<int> a(n), max_median(n), min_median(n), h(n, 1);
	BIT<int> bit(n);

	for(int& v : a) cin >> v;

	auto _ = a;

	sort(_.begin(), _.end());

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	
	function<void(int, int)> dfs = [&](int u, int p) {
		bool leaf = true;

		int k = lower_bound(_.begin(), _.end(), a[u]) - _.begin();
		
		bit.upd(k, 1);

		max_median[u] = -INF;
		min_median[u] = INF;

		for(int v : g[u]) {
			if(v == p) continue;
			leaf = false;
			h[v] = 1 + h[u];
			dfs(v, u);
			max_median[u] = max(min_median[v], max_median[u]);
			min_median[u] = min(max_median[v], min_median[u]);
		}

		if(leaf) {
			if(h[u] % 2) max_median[u] = min_median[u] = _[bit.find_by_order(h[u] / 2 + 1) - 1];
			else {
				int x = _[bit.find_by_order(h[u] / 2) - 1] + _[bit.find_by_order(h[u] / 2 + 1) - 1];
				max_median[u] = min_median[u] = x / 2;
			}
		}

		bit.upd(k, -1);
	};

	dfs(0, 0);

	cout << max_median[0] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
