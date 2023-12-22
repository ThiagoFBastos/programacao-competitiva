#include "bits/stdc++.h"
using namespace std;

void solve() {
	int n, d, a;
	cin >> n >> d >> a;
	vector<pair<int, int>> m(n);
	vector<long long> pre(n + 2, 0);
	for(int i = 0; i < n; ++i) {
		int x, h;
		cin >> x >> h;
		m[i] = {x, h};
	}
	sort(m.begin(), m.end());
	int k = 0; 
	long long ans = 0;
	for(int i = 1; i <= n; ++i) {
		pre[i] += pre[i - 1];
		auto [x, h] = m[i - 1];
		while(k < n && x + 2LL * d >= m[k].first) ++k;
		if(h - pre[i] > 0) {
			long long x = (h - pre[i] + a - 1) / a;
			pre[i] += a * x;
			pre[k + 1] -= a * x;
			ans += x;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
