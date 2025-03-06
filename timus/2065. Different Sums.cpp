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
	int n, k;
	cin >> n >> k;
	for(int i = 0; i < k - 1; ++i) {
		if(i % 2 == 0) cout << i / 2 + 1 << ' ';
		else cout << -i / 2 - 1 << ' ';
	}
	for(int i = k - 1; i < n; ++i) cout << "0 ";
	cout << "\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}