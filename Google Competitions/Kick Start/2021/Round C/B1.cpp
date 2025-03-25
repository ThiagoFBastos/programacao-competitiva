#include "bits/stdc++.h"
using namespace std;
int caso;
void solve() {
	long long x;
	int cnt = 0;
	cin >> x;
	vector<long long> p;
	x <<= 1;
	for(int k = 1; 1LL * k * k <= x; ++k) {
		if(x % k) continue;
		p.push_back(k);
		if(x != 1LL * k * k) p.push_back(x / k);
	}
	for(auto n : p) {
		auto m = x / n;
		if(n < m || (n + m - 1) % 2) continue;
		auto R = (n + m - 1) / 2;
		auto L = n - R;
		if(R < L || R - L + 1 != m) continue;
		++cnt;
	}
	cout << "Case #" << caso << ": " << cnt << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(caso = 1; caso <= t; ++caso) solve();
	return 0;
}