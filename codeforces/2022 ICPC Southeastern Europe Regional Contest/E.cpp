#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2,sse3")
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

	vector<ii> a(2 * n);
	i64 dp[2] = {0, INFLL};

	for(int i = 0; i < 2 * n; ++i) {
		cin >> a[i].fi;
		a[i].sc = i;
	}

	sort(all(a));

	for(int i = 0; i < 2 * n; i += 2) {
		i64 new_dp[2] = {INFLL, INFLL};
		if(a[i].sc / 2 == a[i + 1].sc / 2) {
			new_dp[1] = dp[0] - a[i].fi - a[i + 1].fi;
			new_dp[1] = min(new_dp[1], dp[1] + min(a[i].fi - a[i + 1].fi, a[i + 1].fi - a[i].fi));
			new_dp[0] = dp[1] + a[i].fi + a[i + 1].fi;
		} else {
			for(int j = 0; j < 2; ++j) new_dp[j] = min(new_dp[j], dp[j] + a[i+1].fi-a[i].fi);
			new_dp[1] = min(new_dp[1], dp[0] - a[i].fi - a[i + 1].fi);
			new_dp[1] = min(new_dp[1], dp[1] + min(a[i].fi - a[i + 1].fi, a[i + 1].fi - a[i].fi));
			new_dp[0] = min(new_dp[0], dp[1] + a[i].fi + a[i + 1].fi);
		}
		dp[0] = new_dp[0], dp[1] = new_dp[1];
	}
	
	cout << dp[0] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

