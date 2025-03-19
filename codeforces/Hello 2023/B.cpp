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

	if(n % 2 == 0) {
		cout << "YES\n";
		for(int i = 0; i < n; ++i) cout << (i % 2 ? -1 : 1) << ' ';
		cout << '\n';
	} else {
		int m = n / 2;
		for(int k = -5000; k <= 5000; ++k) {
			int j = -m * k;
			if(m == 1 || j % (m - 1)) continue;
			j /= m - 1;
			if(abs(j) > 5000 || !j) continue;
			cout << "YES\n";
			for(int i = 0; i < n; ++i) cout << (i % 2 ? j : k) << ' ';
			cout << '\n';
			return;
		}
		cout << "NO\n";
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
