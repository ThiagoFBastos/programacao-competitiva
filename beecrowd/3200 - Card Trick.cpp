#include "bits/stdc++.h"
using namespace std;
void solve() {
	int n;
	cin >> n;
	queue<int> q;
	vector<int> p(n);
	for(int i = 0; i < n; ++i) q.push(i);
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < i; ++j) {
			int v = q.front();
			q.pop();
			q.push(v);
		}
		int v = q.front();
		p[v] = i;
		q.pop();
	}
	for(int i = 0; i < n - 1; ++i) cout << p[i] << ' ';
	cout << p[n - 1] << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}