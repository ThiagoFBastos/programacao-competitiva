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
	int n, m;

	cout.precision(9);
	cout.setf(ios_base :: fixed);

	while(cin >> n >> m) {
		int lo = 1, s = 0;

		m += n;

		for(int i = 1; i <= n; ++i) {
			while(lo < m && abs(m * i - n * lo) > abs(m * i - n * (lo + 1))) ++lo;
			s += abs(m * i - n * lo);		
		}

		cout << 1e4 * s / (n * m) << '\n';
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