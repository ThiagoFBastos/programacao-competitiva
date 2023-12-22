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
	int n, q;

	cin >> n;

	vector<ii> pairs;
	map<ii, int> mp;

	for(int i = 1; i <= n; ++i) {
		for(int j = 0; i + (1 << j) - 1 <= n; ++j) {
			int l = i, r = i + (1 << j) - 1;	
			pairs.pb({l, r});
			mp[{l, r}] = pairs.size();
		}
	}

	cout << pairs.size() << '\n';
	for(auto [l, r] : pairs) cout << l << ' ' << r << '\n';
	cout.flush();

	cin >> q;

	while(q--) {
		int L, R;
		cin >> L >> R;
		int k = 31 - __builtin_clz(R - L + 1);
		int a = mp[{L, L + (1 << k) - 1}];
		int b = mp[{R - (1 << k) + 1, R}];
		cout << a << ' ' << b << '\n';
		cout.flush();
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
