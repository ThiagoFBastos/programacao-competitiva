#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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
	int n;

	cin >> n;

	vector<pair<i64, int>> a(n);

	for(int i = 0; i < n; ++i) {
		cin >> a[i].fi;
		a[i].sc = i + 1;
	}

	sort(all(a));

	cout << n - 1 << '\n';

	for(int i = 1; i < n; ++i) {
		i64 x = (a[i].fi + a[i - 1].fi - 1) / a[i - 1].fi * a[i - 1].fi;
		cout << a[i].sc << ' ' << x - a[i].fi << '\n';
		a[i].fi = x;
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
