#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {

	int n, k;
	i64 m;

	cin >> n >> k >> m;

	vector<i64> a(n);
	vector<int> to(n), cur(n), tmp(n);
	int l = 0, r = k;

	for(i64& v : a) cin >> v;

	for(int i = 0; i < n; ++i) {
		while(r < i) ++l, ++r;
		while(r < n - 1 && abs(a[i] - a[l]) > abs(a[i] - a[r + 1])) ++l, ++r;
		to[i] = abs(a[i] - a[l]) >= abs(a[i] - a[r]) ? l : r;
		cur[i] = i;
	}

	for(int i = 0; (1ll << i) <= m; ++i) {

		if(m & (1ll << i)) {
			for(int j = 0; j < n; ++j)
				cur[j] = to[cur[j]];
		}
	
		for(int j = 0; j < n; ++j) tmp[j] = to[to[j]];

		swap(tmp, to);
	}

	for(int i : cur) cout << i + 1 << ' ';
	cout << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
