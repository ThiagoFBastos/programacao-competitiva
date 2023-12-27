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
	int n, k;
	cin >> n >> k;
	vector<i64> ps(n + 1, 0), pm(n + 1, 0);
	i64 ans = 0;
	for(int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		ps[i] = ps[i - 1] + a;
		pm[i] = pm[i - 1] + max(a, 0);
	}
	for(int i = 1; i <= n - k + 1; ++i) {
		i64 cost = pm[n] - pm[i + k - 1] + pm[i - 1] + max(0ll, ps[i + k - 1] - ps[i - 1]);
		ans = max(ans, cost);
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
