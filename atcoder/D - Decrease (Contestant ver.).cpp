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
	i64 k;
	const i64 maxn = 1e16L + 1000;

	cin >> k;

	if(!k) {
		cout << "2\n0 0\n";
		return;
	}

	for(int n = 2; n <= 50; ++n) {
		i64 x = k / n + n - 1;
		int r = k % n;
		if(x + n * (!!r) <= maxn && x - r >= 0) {
			cout << n << '\n';
			for(int i = 0; i < r; ++i) cout << x + n - r + 1 << ' ';
			for(int i = r; i < n; ++i) cout << x - r << ' ';
			cout << '\n';
			break;
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

