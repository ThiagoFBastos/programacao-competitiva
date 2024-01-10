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

const int mod = 998244353;

void solve() {
	
	int n, m, k;

	cin >> n >> m >> k;

	vector<vector<int>> g(n);
	vector<int> cnt(n + 1, 0);

	while(m--) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for(int i = 0; i < n; ++i) {
		auto& v = g[i];
		v.push_back(n);
		v.push_back(i);
		sort(v.begin(), v.end());
	}

	cnt[0] = 1;

	for(int i = 0; i < k; ++i) {
		vector<int> pre(n + 1, 0);

		for(int v = 0; v < n; ++v) {
			int last = 0;
			for(int u : g[v]) {
				pre[last] += cnt[v];
				if(pre[last] >= mod) pre[last] -= mod;
				pre[u] -= cnt[v];
				if(pre[u] < 0) pre[u] += mod;
				last = u + 1;
			}
		}

		for(int j = 1; j < n; ++j) {
			pre[j] += pre[j - 1];
			if(pre[j] >= mod) pre[j] -= mod;
		}

		swap(pre, cnt);
	}

	cout << cnt[0] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
