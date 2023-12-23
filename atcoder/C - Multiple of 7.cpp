#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n;
	cin >> n;
	string s;
	while(n > 0) {
		int k = 0;
		while(k * (k - 1ll) / 2 + k <= n) ++k;
		--k;
		n -= k * (k - 1ll) / 2 + k;
		s += string(k, '7');
		if(n > 0) s += 'x';
	}
	int p = 1;
	for(char& ch : s) {
		if(ch == 'x') {
			for(int k = 1; k < 7; ++k) {
				if(k * p % 7 == 1) {
					ch = k + '0';
					break;
				}
			}
		}
		p = 10 * p % 7;
	}
	reverse(s.begin(), s.end());
	cout << s << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
 	return 0;
}
