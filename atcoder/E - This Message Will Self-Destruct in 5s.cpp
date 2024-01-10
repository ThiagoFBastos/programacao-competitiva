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

	map<int, int> cnt;
	i64 ans = 0;

	for(int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		auto k = cnt.find(i - a);
		if(k != cnt.end()) ans += k->second;
		++cnt[i + a];
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

