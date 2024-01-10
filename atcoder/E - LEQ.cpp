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

const int mod = 998244353;

vector<int> bit;

void upd(int k, int x) {
	for(++k; k < (int)size(bit); k += k & -k) {
		bit[k] += x;
		if(bit[k] >= mod) bit[k] -= mod;
	}
}

int query(int k) {
	int ans {};
	for(++k; k > 0; k -= k & -k) {
		ans += bit[k];
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

i64 exp(i64 n, int p) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}

void solve() {
	
	int n, ans = 0;
	
	cin >> n;
	
	vector<int> a(n);
	
	for(int& x : a) cin >> x;
	
	auto p = a;
	
	sort(p.begin(), p.end());
	
	bit.assign(n + 1, 0);

	for(int i = 1; i <= n; ++i) {
		int k = lower_bound(p.begin(), p.end(), a[i - 1]) - p.begin();
		ans = (ans + query(k) * exp(2, i)) % mod;
		upd(k, exp(exp(2, i + 1), mod - 2));
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
