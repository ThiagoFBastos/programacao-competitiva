#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const ld eps = 1e-9;

int tcase;

void solve() {
	int q;
	cin >> q;
	vector<int> ans(q, 0);
	map<int, vector<pair<ld, int>>> query;

	for(int i = 0; i < q; ++i) {
		int n, r;
		u64 p;
		cin >> n >> r >> p;
		query[r].emplace_back(p / (ld)n, i);
	}

	for(auto& [r, v] : query) {
		ld k = 1;
		int y = 0;
		sort(v.rbegin(), v.rend());
		while(!v.empty()) {			
			while(!v.empty() && k - v.back().first > -eps) {
				ans[v.back().second] = y;
				v.pop_back();
			}
			k *= (100.0L + r) / 100.0L;
			++y;
		}
	}

	for(int i = 1; i <= q; ++i)
		cout << "Case " << i << ": " << ans[i - 1] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
