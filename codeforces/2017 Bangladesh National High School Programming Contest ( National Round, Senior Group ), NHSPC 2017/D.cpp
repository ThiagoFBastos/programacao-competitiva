#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

int tcase;

void solve() {
	
	int n;

	cin >> n;

	vector<int> a(n);
	int X = 0, ans = 0;

	for(int& v : a) {
		cin >> v;
		X ^= v;
	}

	if(X) for(int v : a) ans += v > (v ^ X);

	cout << "Case " << ++tcase << ": " << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
 
