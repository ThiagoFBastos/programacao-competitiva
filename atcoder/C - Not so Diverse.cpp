#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> frq(n + 1, 0);
	int ans = 0, m = 0;

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		++frq[a];
	}

	for(int v : frq) m += !!v;

	sort(frq.begin(), frq.end());
	
	for(int i = 0; i < n && m > k; ++i) {
		ans += frq[i];
		m -= !!frq[i];
		frq.back() += frq[i];
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
 
