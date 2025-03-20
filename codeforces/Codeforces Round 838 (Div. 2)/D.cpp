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

int query(int i, int j) {
	cout << "? " << i << ' ' << j << '\n';
	cout.flush();
	int g;
	cin >> g;
	return g;
}

void solve() {
	int n;

	cin >> n;

	int gij = query(1, 2), i = 1, j = 2;

	for(int k = 3; k <= n; ++k) {
		int gki = query(k, i);
		int gkj = query(k, j);
		int g = max({gij, gki, gkj});
		if(g == gki) j = k;
		else if(g == gkj) i = k;
		gij = max(g, gij);
	}

	cout << "! " << i << ' ' << j << '\n';
	cout.flush();
	int ans;
	cin >> ans;
	if(ans < 0) exit(0);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
