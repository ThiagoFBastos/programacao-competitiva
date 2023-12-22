#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 3e5 + 10;

int bit[N];

void upd(int k, int x, int n) {
	for(++k; k <= n; k += k & -k) bit[k] += x;
}

int query(int k) {
	int ans = 0;
	for(++k; k > 0; k -= k & -k) ans += bit[k];
	return ans;
}

void solve() {

	int n;

	cin >> n;

	vector<int> a(n), c(n);
	map<int, vector<int>> S;

	i64 ans = 0;

	for(int& v : c) cin >> v;
	for(int& v : a) cin >> v;

	for(int i = 0; i < n; ++i) {
		ans += i - query(a[i]);
		upd(a[i], 1, n + 1);
		S[c[i]].push_back(a[i]);
	}

	for(auto& [x, y] : S) {
		auto p = y;

		sort(p.begin(), p.end());

		for(int& v : y) v = lower_bound(p.begin(), p.end(), v) - p.begin();
			
		int m = y.size();
		memset(bit, 0, (m + 1) * sizeof(int));

		for(int i = 0; i < m; ++i) {
			ans -= i - query(y[i]);
			upd(y[i], 1, m + 1);
		}

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

