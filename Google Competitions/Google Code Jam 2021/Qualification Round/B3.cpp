#include "bits/stdc++.h"
using namespace std;
const int inf = 1e9;
void solve() {
	int x, y, C = inf, J = inf;
	string s;
	cin >> x >> y >> s;
	if(s[0] == '?') C = J = 0;
	else if(s[0] == 'C') C = 0;
	else J = 0;
	for(int i = 1; i < size(s); ++i) {
		if(s[i] == '?') {
			int c, j;
			c = min(C, J + y);
			j = min(J, C + x);
			C = c, J = j;
		} else if(s[i] == 'J') {
			J = min(J, C + x);
			C = inf;
		} else {
			C = min(C, J + y);
			J = inf;
		}
	}
	cout << min(C, J) << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}