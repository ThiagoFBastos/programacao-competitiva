#include "bits/stdc++.h"
using namespace std;
void solve() {
	string s;
	int n;
	cin >> n >> s;
	vector<int> pre(n);
	pre[0] = 1;
	for(int k = 1; k < n; ++k) {
		if(s[k] > s[k - 1]) pre[k] = 1 + pre[k - 1];
		else pre[k] = 1;
	}
	for(int x : pre) cout << x << ' ';
	cout << '\n';
}	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Case #" << k << ": ";
		solve();
	}
	return 0;
}