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
	int n, q, s, t;
	i64 temp = 0;
	
	cin >> n >> q >> s >> t;
	
	vector<int> a(n + 1);
	BIT<i64> bit(n + 1);
	
	for(int& v : a) cin >> v;
	
	for(int i = 0; i <= n; ++i) {
		bit.upd(i, a[i]);
		bit.upd(i + 1, -a[i]);
	}
	
	s *= -1;
	
	for(int i = 1; i <= n; ++i) {
		if(a[i - 1] < a[i]) temp += s * (a[i] - a[i - 1] + 0ll);
		else temp += t * (a[i - 1] - a[i] + 0ll);
	}
	
	auto undo = [&](int i) {
		i64 L = bit.query(i - 1), R = bit.query(i);
		if(L < R) temp -= s * (R - L);
		else temp -= t * (L - R);
	};
	
	auto doit = [&](int i) {
		i64 L = bit.query(i - 1), R = bit.query(i);
		if(L < R) temp += s * (R - L);
		else temp += t * (L - R);	
	};
	
	while(q--) {
		int l, r, x;
		
		cin >> l >> r >> x;
		
		undo(l);
	
		if(r < n) undo(r + 1);
		
		bit.upd(l, x);
		bit.upd(r + 1, -x);
		
		doit(l);
		if(r < n) doit(r + 1);
		
		cout << temp << '\n';
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
