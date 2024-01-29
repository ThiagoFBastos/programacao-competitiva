#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;

const int INF = 1e9;

void solve() {
	
	int n, h;

	cin >> n >> h;

	vector<int> x(2 * n + 1);

	for(int i = 0; i < 2 * n; ++i) cin >> x[i];

	x.back() = x[2 * n - 1];

	int hi = 2 * n - 1, ans = 0, X = 0, H = 0;

	for(int i = n - 1; i >= 0; --i) {
		X += x[2 * i + 1] - x[2 * i];
		H += x[2 * i + 2] - x[2 * i + 1];

		while(H > h) {
			if(hi & 1) H -= x[hi + 1] - x[hi];
			else X -= x[hi + 1] - x[hi];
			--hi;
		}

		if(H == h && hi % 2 == 0) {
			X -= x[hi + 1] - x[hi];
			--hi;
		}

		if(H == h && hi == 2 * n - 1) {
			X -= x[2 * n - 1] - x[2 * n - 2];
			hi = 2 * n - 3;
		}
	
		ans = max(ans, X + h);
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

