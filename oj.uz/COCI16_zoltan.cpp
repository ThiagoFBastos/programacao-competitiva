#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;	
 
const int MOD = 1e9 + 7;
 
i64 exp(i64 n, int p, int m) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % m;
		n = n * n % m;
	}
	return ans;
}
 
template<int m>
struct modInt {
	int val;
	
	modInt() {val = 0;}
	modInt(int val) : val {val} {}
	
	modInt operator^(int p) {
		return {exp(val, p, m)};
	}
	
	modInt& operator^=(int p) {
		val = exp(val, p, m);
		return *this;
	}
 
	modInt operator+(modInt x) {
		int ans = val + x.val;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(modInt x) {
		int ans = val - x.val;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(modInt x) {
		val += x.val;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(modInt x) {
		val -= x.val;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(modInt x) {
		return {((i64)val * x.val % m + m) % m};
	}
 
	modInt& operator*=(modInt x) {
		val = ((i64)val * x.val % m + m) % m;
		return *this;
	}
	
	modInt operator/(modInt x) {
		return {(val * exp(x.val, m - 2, m) % m + m) % m};
	}
	
	modInt& operator/=(modInt x) {
		val = (val * exp(x.val, m - 2, m) % m + m) % m;
		return *this;
	}
	
	modInt operator+(int x) {
		x = (x % m + m) % m;
		int ans = val + x;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(int x) {
		x = (x % m + m) % m;
		int ans = val - x;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(int x) {
		x = (x % m + m) % m;
		val += x;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(int x) {
		x = (x % m + m) % m;
		val -= x;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(int x) {
		x = (x % m + m) % m;
		return {int((i64)val * x % m)};
	}
	
	modInt& operator*=(int x) {
		x = (x % m + m) % m;
		val = (i64)val * x % m;
		return *this;
	}
	
	modInt operator/(int x) {
		return {val * exp(x, m - 2, m) % m};
	}
	
	modInt& operator/=(int x) {
		val = val * exp(x, m - 2, m) % m;
		return *this;
	}
};
 
template<int m>
ostream& operator<<(ostream& os, modInt<m> v) {
	os << v.val;
	return os;
}
 
template<int m>
istream& operator>>(istream& is, modInt<m>& v) {
	is >> v.val;
	return is;
}
 
struct op {
	pair<int, modInt<MOD>> operator()(pair<int, modInt<MOD>> a, pair<int, modInt<MOD>> b) {
		if(a.fi < b.fi) return b;
		else if(a.fi > b.fi) return a;
		a.sc += b.sc;
		return a;
	}
};
 
template<class T, class op>
struct BIT {
	vector<T> bit;
	T def;
 
	BIT(int n, T _def) : def {_def} {
		bit.assign(n + 1, _def);
	}
	
	void upd(int k, T x) {
		op cmp;
		for(++k; k < int(bit.size()); k += k & -k) bit[k] = cmp(bit[k], x);
	}
	
	T query(int k) {
		T ans = def;
		op cmp;
		for(++k; k > 0; k -= k & -k) ans = cmp(ans, bit[k]);
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return op()(query(r), -query(l - 1));
	}
};
void solve() {
	int n;
 
	cin >> n;
 
	vector<int> a(n);
	BIT<pair<int, modInt<MOD>>, op> bit(n, make_pair(0, 0));
 
	for(int& v : a) cin >> v;
 
	auto p = a;
 
	sort(all(p));
 
	reverse(all(a));
 
	for(int& v : a) v = lower_bound(all(p), v) - p.begin();
	for(int i = n - 2; i >= 0; --i) a.pb(a[i]);
 
	int k = exp(2, MOD - 2, MOD);
 
	for(int i = 0; i < (int)a.size(); ++i) {
		int v = a[i];
		auto r = bit.query(v - 1);
		if(++r.fi == 1) r.sc = 1;
		r.sc *= i != n - 1 ? k : 1;
		bit.upd(v, r);
	}
 
	auto [lis, cnt] = bit.query(n - 1);
 
	cout << lis << ' ' << cnt * exp(2, n - 1, MOD) << '\n'; 
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
