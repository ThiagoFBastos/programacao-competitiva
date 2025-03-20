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

void solve() {
	int n;
	i64 ans = 0;
	map<vector<int>, i64> dp;

	cin >> n;

	vector<int> a(n);

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		if(!a[i]) ans += (i+1ll)*(n-i);
	}

	dp[{}] = 1;

	for(int i = 0; i < n; ++i) {

		if(!a[i]) {
			++dp[{}];
			continue;
		}

		map<vector<int>, i64> new_dp;
	
		new_dp[{}] = 1;

		for(auto &[e, k] : dp) {
			auto e_new = e;
			bool ok = false;
			for(int j = 0; j < (int)e.size(); ++j) {
				if(a[i] & e[j]) {
					e_new[j] = a[i];
					ok = true;
					break;
				}
			}
			if(!ok) {
				e_new.pb(a[i]);
				ans += k * (n - i);
			}
			new_dp[e_new] += k;
		}

		swap(new_dp, dp);
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
