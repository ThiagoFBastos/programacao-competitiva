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
	string s;
	cin >> s;
	n = s.size();
	auto ans = make_tuple(INT_MIN, 0, 0);
	for(char ch : "RB"s) {
		int lo = 0, sum = 0;
		for(int i = 0; i < n; ++i) {
			int x = ch == s[i] ? 1 : -1;
			sum += x;
			ans = max(ans, make_tuple(sum, -lo - 1, -i - 1));
			if(sum < 0) sum = 0, lo = i + 1;
		}
	}
	auto [S, l, r] = ans;
	l *= -1, r *= -1;
	cout << l << ' ' << r << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
