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

void solve() {

	int n;
	i64 cnt = 0;

	cin >> n;

	for(int i = 1; i <= n; ++i) cnt += (n - i + 1ll) * i;

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		if(u > v) swap(u, v);
		cnt -= u * (n - v + 1ll);
	}

	cout << cnt << '\n';
}


int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
