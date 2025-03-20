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
	int n, m;
		
	cin >> n >> m;

	using matrix = vector<vector<int>>;
	matrix a(n), ps(n + 1);

	for(int i = 0; i <= n; ++i) ps[i].assign(m + 1, 0);

	for(int i = 0; i < n; ++i) {
		a[i].resize(m);
		for(int& v : a[i]) cin >> v;
	}

	int lo = 1, hi = min(n, m) + 1;

	auto query = [](matrix& ps, int x0, int y0, int x1, int y1) {
		return ps[x1][y1] - ps[x0 - 1][y1] - ps[x1][y0 - 1] + ps[x0 - 1][y0 - 1];
	};

	while(lo < hi) {
		int mid = (lo + hi) / 2;
		bool ok = false;

		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= m; ++j) {
				ps[i][j] = a[i - 1][j - 1] >= mid;
				ps[i][j] += ps[i - 1][j];
				ps[i][j] += ps[i][j - 1];
				ps[i][j] -= ps[i - 1][j - 1];
			}
		}

		for(int i = 1; i <= n - mid + 1; ++i)
			for(int j = 1; j <= m - mid + 1; ++j)
				ok = ok || query(ps, i, j, i + mid - 1, j + mid - 1) == (i64)mid * mid;
				
		if(!ok) hi = mid;
		else lo = mid + 1;
	}

	cout << hi - 1 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

