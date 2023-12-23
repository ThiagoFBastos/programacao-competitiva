#pragma GCC optimize("O3")

#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

auto divisors(int x) {
	vector<int> a;
	for(int k = 1; k * k <= x; ++k) {
		if(x % k) continue;
		a.push_back(k);
		a.push_back(x / k);
	}
	return a;
}

void solve() {	
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	
	for(int i = 0; i < n; ++i) cin >> a[i] >> b[i];
	
	auto p = divisors(a[0]);
	auto q = divisors(b[0]);
	auto ans = 0LL;
	
	for(int x : p) {
		for(int y : q) {
			bool ok = true;
			for(int i = 0; i < n; ++i)
				ok = ok && (a[i] % x + b[i] % y == 0 || a[i] % y + b[i] % x == 0); 
			if(ok) ans = max(ans, lcm(0ll + x, 0ll + y));
		}
	}
	
	cout << ans << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
