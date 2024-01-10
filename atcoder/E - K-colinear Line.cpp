#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 310;

bool vis[MAXN][MAXN];

i64 cross(ii a, ii b) {
	auto [x0, y0] = a;
	auto [x1, y1] = b;
	return (i64)x0 * y1 - (i64)x1 * y0;
}

void solve() {
	int n, k, ans = 0;

	cin >> n >> k;

	vector<ii> p(n);
	
	for(auto& [x, y] : p) cin >> x >> y;

	if(k == 1) {
		cout << "Infinity\n";
		return;
	}

	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			auto [x0, y0] = p[i];
			auto [x1, y1] = p[j];
			auto u = make_pair(x1 - x0, y1 - y0);
			int cnt = 0, L = n, R = 0;
			for(int k = 0; k < n; ++k) {
				auto [x2, y2] = p[k];
				auto v = make_pair(x2 - x0, y2 - y0);
				if(cross(u, v) == 0) {
					++cnt;
					L = min(L, k);
					R = max(R, k);
				}
			}
			if(vis[L][R]) continue;
			vis[L][R] = true;
			if(cnt >= k) ++ans;
		}
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
