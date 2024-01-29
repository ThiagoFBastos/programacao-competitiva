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
	vector<ii> ans;
	for(int i = 2; i < n; ++i) {
		if(n % i == 0) ans.emplace_back(i, i);
		if(n % (2 * i - 1) == 0 || n % (2 * i - 1) == i) ans.emplace_back(i, i - 1);	
	}
	sort(ans.begin(), ans.end());
	cout << n << ":\n";
	for(auto [x, y] : ans) cout << x << ',' << y << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
