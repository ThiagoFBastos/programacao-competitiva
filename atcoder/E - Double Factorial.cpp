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

i64 f(i64 n) {
	i64 cnt = 0;
	while(n > 0) cnt += n /= 5;
	return cnt;
}

void solve() {
	
	i64 n;

	cin >> n;

	if(n % 2 == 0) cout << f(n / 2) << '\n';
	else cout << "0\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
