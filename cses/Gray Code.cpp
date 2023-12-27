#include "bits/stdc++.h"
using namespace std;
vector<int> v[17];
string to_bin(int x, int k) {
	string s;
	for(; x > 0; x /= 2) s += x % 2 + '0';
	while(size(s) < k) s += "0";
	reverse(s.begin(), s.end());
	return s;
}
void solve() {
	int n, x = 0;
	cin >> n;
	v[0] = {0};
	for(int k = 1; k <= n; ++k) {
		for(int i : v[k - 1]) v[k].push_back(i);
		v[k - 1][0] = 1 << (k - 1);
		for(int i : v[k - 1]) v[k].push_back(i);
	}
	for(int y : v[n]) {
		x ^= y;
		cout << to_bin(x, n) << '\n';
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
