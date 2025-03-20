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
	
	int m = 1;

	while(m < n) m <<= 1;
	m <<= 1;
	
	vector<int> mp(m + 1, 0);
	i64 cnt = n * (n + 1ll) / 2;
	++mp[0];
	
	for(int i = 0, ps = 0; i < n; ++i) {
		int a;
		cin >> a;
		ps ^= a;
		for(int j = 0; j * j <= m; ++j) {
			int X = ps ^ (j * j);
			if(X > m) continue;
			cnt -= mp[X];
		}
		++mp[ps];
	}

	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

