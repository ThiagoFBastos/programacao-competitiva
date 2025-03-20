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

	vector<i64> a(n);
	bool good = true;

	for(i64& v : a) cin >> v;

	sort(all(a));

	for(int i = 1; i < n; ++i) good = good && a[i] != a[i - 1];

	for(int p = 2; p <= 100; ++p) {
		vector<bool> vis(p, false);
		for(int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) {
				int x = a[i] % p, y = a[j] % p;
				if(x != y) continue;
				vis[x] = true;
			}
		}
		good = good && count(all(vis), false);
	}

	if(good) cout << "YES\n";
	else cout << "NO\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

