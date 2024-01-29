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
	string s;
	cin >> n >> k >> s;
	
	vector<int> w(n + 1, 0), b(n + 1, 0);
	int ans = 0;
	
	for(int i = 1; i <= n; ++i) {
		w[i] = w[i - 1];
		b[i] = b[i - 1];
		if(s[i - 1] == 'W') ++w[i];
		else ++b[i];
		if(b[i] <= k) ans = max(ans, w[i]);
	}
	
	for(int i = n - 1; i >= 0; --i) {
		if(b[n] - b[i] > k) break;
		int j = upper_bound(b.begin(), b.end(), k - b[n] + b[i]) - b.begin() - 1;
		ans = max(ans, w[n] - w[i] + w[min(j, i)]);
	}
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
 	return 0;
}


