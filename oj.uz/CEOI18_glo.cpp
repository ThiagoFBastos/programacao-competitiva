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
 
template<class T>
struct BIT {
	vector<T> bit;
	
	BIT() {}
 
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] = max(bit[k], x);
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans = max(ans, bit[k]);
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};
 
void solve() {	
	
	int n, x;
 
	cin >> n >> x;
 
	vector<int> a(n);
 
	for(int& v : a) cin >> v;
 
	auto p = a;
	sort(p.begin(), p.end());
 
	BIT<int> dp[2];
	int ans = 0;
 
	for(int j = 0; j < 2; ++j) {
		for(int i = 0; i < 2; ++i) dp[i] = BIT<int>(n);
		for(int i = 0; i < n; ++i) {
			int k = lower_bound(p.begin(), p.end(), a[i]) - p.begin();
			int j = upper_bound(p.begin(), p.end(), a[i] + x - 1) - p.begin() - 1;
			dp[1].upd(k, 1 + max(dp[1].query(k - 1), dp[0].query(j)));
			dp[0].upd(k, 1 + dp[0].query(k - 1));
		}
		ans = max(ans, dp[1].query(n - 1));
		for(int& v : a) v *= -1;
		for(int& v : p) v *= -1;
		reverse(p.begin(), p.end());
		reverse(a.begin(), a.end());
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
