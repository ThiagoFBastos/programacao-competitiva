#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

using T = tuple<int, int, int>;

void solve() {
	int n, m, k;

	cin >> n >> m >> k;

	vector<T> a(k);
	vector<bool> vis(k, false);
	queue<int> q;

	for(int i = 0; i < k; ++i) {
		int x, y, r;
		cin >> x >> y >> r;
		if(x - r <= 0 || y + r >= m) {
			vis[i] = true;
			q.push(i);
		}
		a[i] = {x, y, r};
	}

	while(!q.empty()) {
		int i = q.front();
		q.pop();
		auto [x0, y0, r0] = a[i];
		if(y0 - r0 <= 0 || x0 + r0 >= n) {
			cout << "N\n";
			return;
		}
		for(int j = 0; j < k; ++j) {
			if(vis[j]) continue;
			auto [x1, y1, r1] = a[j];
			i64 X = (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
			i64 Y = (r0 + r1) * (r0 + r1);
			if(X <= Y) {
				vis[j] = true;
				q.push(j);
			}
		}
	}

	cout << "S\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
