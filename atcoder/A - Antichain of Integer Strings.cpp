#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;

int LOG(int x) {
	if(x < 10) return 0;
	return 1 + LOG(x / 10);
}

int POW(int x) {
	if(x == 0) return 1;
	return 10 * POW(x - 1);
}

void solve() {
	
	i64 l, r, ans;

	cin >> l >> r;

	int R = LOG(r);
	int L = LOG(l);

	ans = r - max<i64>(l, POW(R)) + 1;
 
	if(R > L) {
		string s = to_string(r);
		if(s[0] == '1') {
			string p(s.begin() + 1, s.end());
			i64 X = POW(R);
			i64 ll = max(l, max(stoi(p) + 1ll, X / 10)), rr = X - 1;
			if(ll <= rr) {
				i64 T = rr - ll + 1;
				
				l = X / 10;
				r /= 10;

				ll = max(l, ll);
				rr = min(r, rr);

				if(ll <= rr) T -= rr - ll + 1;

				ans += T;
			}
		}
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
