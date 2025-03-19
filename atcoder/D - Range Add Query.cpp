#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

void solve() {
	int n, k, q;

	cin >> n >> k;

	vector<int> sig(k + 1);
	vector<i64> a(n), sum(k, 0);
	vector<vector<ii>> query(n);
	
	for(i64& v : a) cin >> v;
		
	for(int i = 0; i < n; ++i)
		for(int j = max(0, i - k + 1); j < i; ++j)
			a[i] -= a[j];

	sig[0] = -1;

	for(int i = 1; i <= k; ++i) {
		sig[i] = 0;
		for(int j = max(0, i - k + 1); j < i; ++j) sig[i] -= sig[j];
	}

	cin >> q;

	vector<bool> ans(q, true);

	for(int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		--l, --r;
		query[l].pb({r, i});
	}

	for(int i = 0; i <= n - k; ++i) {
		for(auto [r, id] : query[i]) {
			for(int j = r - k + 2; j <= r; ++j)
				ans[id] = ans[id] && a[j] + sum[j % k] == 0;
		}
		a[i] += sum[i % k];
		for(int j = 1; j <= k; ++j)
			sum[(i + j) % k] += sig[j] * a[i];		
	}

	for(bool v : ans) cout << (v ? "Yes\n" : "No\n");
}			

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}