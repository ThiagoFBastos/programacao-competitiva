#include "bits/stdc++.h"
using namespace std;
using event = tuple<int, int, int>;
void solve() {
	int a, b, c, d, ans = 0, tipo[2] = {0, 0};
	vector<event> e;
	cin >> a >> b >> c >> d;
	for(int k = 1; k * k <= max(b, d); ++k) {
		int x = d / k - (c - 1) / k;
		int y = b / k - (a - 1) / k;
		int L, R;
		if(x && y) {
			ans = max(ans, k);
			L = (c + k - 1) / k, R = d / k + 1;
			e.push_back({L, 1, 0});
			e.push_back({R, 0, 0});
			L = (a + k - 1) / k, R = b / k + 1;
			e.push_back({L, 1, 1});
			e.push_back({R, 0, 1});	
		} else if(x) {
			L = (c + k - 1) / k, R = d / k + 1;
			e.push_back({L, 1, 0});
			e.push_back({R, 0, 0});
		} else if(y) {
			L = (a + k - 1) / k, R = b / k + 1;
			e.push_back({L, 1, 1});
			e.push_back({R, 0, 1});	
		}
	}
	sort(e.begin(), e.end());
	for(int i = 0, k; i < size(e); ++i) {
		if(get<1>(e[i])) ++tipo[get<2>(e[i])];
		else {
			if(tipo[0] && tipo[1]) ans = max(ans, get<0>(e[i]) - 1);
			--tipo[get<2>(e[i])];
		}
	}
	cout << ans << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}