#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;

void solve() {
	
	int n, m, x0, y0, x1, y1;

	cin >> n >> m >> x0 >> y0 >> x1 >> y1;
	
	int resto = 0;

	for(int x = 1; x <= n; ++x) {
		if(x >= x0 && x <= x1) resto += (y0 - 1) % 2 + (m - y1) % 2;
		else resto += m % 2;
	}

	cout << (1 + resto) / 2 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

