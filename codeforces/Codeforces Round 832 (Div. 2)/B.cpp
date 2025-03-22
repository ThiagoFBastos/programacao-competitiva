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
	int m;

	cin >> m;

	cout << (m + 1) / 2 << '\n';

	int l = 1;

	while(m > 0) {
		if(m == 1) cout << l << ' ' << l + 2 << '\n';
		else cout << l << ' ' << l + m * 3 - 1 << '\n';
		l += 3;
		m -= 2;
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
