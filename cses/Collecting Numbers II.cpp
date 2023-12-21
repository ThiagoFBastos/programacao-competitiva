#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> p(n + 2), a(n + 1);
	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		p[a[i]] = i;
	}
	int ans = 1;
	for(int i = 2; i <= n; ++i) ans += p[i] < p[i - 1];
	p[0] = p[n + 1] = n + 1;
	while(m--) {
		int i, j;
		cin >> i >> j;
		if(i == j) ;
		else if(abs(a[i] - a[j]) == 1) {
			if(a[i] > a[j]) swap(i, j);
			ans -= (p[a[i]] < p[a[i] - 1]) + (p[a[i]] > p[a[i] + 1]) + (p[a[j]] > p[a[j] + 1]);
			swap(a[i], a[j]);
			swap(p[a[i]], p[a[j]]);
			if(a[i] > a[j]) swap(i, j);
			ans += (p[a[i]] < p[a[i] - 1]) + (p[a[i]] > p[a[i] + 1]) + (p[a[j]] > p[a[j] + 1]);
		} else {
			ans -= (p[a[i]] < p[a[i] - 1]) + (p[a[j]] < p[a[j] - 1]) + (p[a[i] + 1] < p[a[i]]) + (p[a[j] + 1] < p[a[j]]);
			swap(a[i], a[j]);
			swap(p[a[i]], p[a[j]]);
			ans += (p[a[i]] < p[a[i] - 1]) + (p[a[j]] < p[a[j] - 1]) + (p[a[i] + 1] < p[a[i]]) + (p[a[j] + 1] < p[a[j]]);
		}
		cout << ans << '\n';
	}
	return 0;
}
