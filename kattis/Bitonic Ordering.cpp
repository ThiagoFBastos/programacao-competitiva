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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
struct BIT {
	vector<T> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};

void solve() {
	
	int n; 
	i64 ans = 0;
	
	cin >> n;
	
	vector<int> a(n), l(n), r(n);
	BIT<int> bit(n);
	vector<ii> p(n);
	
	for(int& v : a) cin >> v;
	
	auto _ = a;
	
	sort(_.begin(), _.end());
	for(int& v : a) v = lower_bound(_.begin(), _.end(), v) - _.begin();
	
	for(int i = 0; i < n; ++i) {
		l[i] = bit.query(a[i], n - 1);
		p[i] = {a[i], i};
		bit.upd(a[i], 1);
	}
	
	bit = BIT<int>(n);
	
	for(int i = n - 1; i >= 0; --i) {
		r[i] = bit.query(a[i], n - 1);
		bit.upd(a[i], 1);
	}
	
	sort(p.begin(), p.end());
	
	for(auto [__, k] : p) ans += min(l[k], r[k]);
	
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
