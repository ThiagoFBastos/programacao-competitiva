#include "bits/stdc++.h"
using namespace std;
void solve() {
	string s;
	cin >> s;
	int n = s.size(), ans = 0;
	vector<int> possible(n + 1, 0);
	for(int k = 1; k < n; ++k) {
		if(n % k) continue;
		for(int i = 0; i < k; ++i) {
			int flag = 1;
			for(int j = i; j < n; j += k) {
				if(s[j] != 'R') {
					flag = 0;
					break;
				}
			}
			possible[k] = flag;
			if(flag) break;
		}
	}
	for(int k = 1; k < n; ++k) ans += possible[__gcd(k, n)];
	cout << ans << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
