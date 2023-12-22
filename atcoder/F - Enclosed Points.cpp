#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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
using i128 = __int128;

i64 exp(i64 n, int p, int m) {
	i64 ans = 1;
	n %= m;
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
	modInt(int v) : val {v} {}
	modInt(i64 v) : val {int((v%m+m)%m)} {}

	modInt operator-() {
		return {-val + (val > 0) * m};
	}

	modInt operator^(i64 p) {
		return {int(exp(val, p, m))};
	}
	
	modInt& operator^=(i64 p) {
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
		return {int(((i64)val * x.val % m + m) % m)};
	}

	modInt& operator*=(modInt x) {
		val = ((i64)val * x.val % m + m) % m;
		return *this;
	}
	
	modInt operator/(modInt x) {
		return {int((val * exp(x.val, m - 2, m) % m + m) % m)};
	}
	
	modInt& operator/=(modInt x) {
		val = (val * exp(x.val, m - 2, m) % m + m) % m;
		return *this;
	}
	
	modInt operator+(i64 x) {
		x = (x % m + m) % m;
		int ans = val + x;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(i64 x) {
		x = (x % m + m) % m;
		int ans = val - x;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(i64 x) {
		x = (x % m + m) % m;
		val += x;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(i64 x) {
		x = (x % m + m) % m;
		val -= x;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(i64 x) {
		x = (x % m + m) % m;
		return {int((i64)val * x % m)};
	}
	
	modInt& operator*=(i64 x) {
		x = (x % m + m) % m;
		val = (i64)val * x % m;
		return *this;
	}
	
	modInt operator/(i64 x) {
		return {int(val * exp(x, m - 2, m) % m)};
	}
	
	modInt& operator/=(i64 x) {
		val = val * exp(x, m - 2, m) % m;
		return *this;
	}

	bool operator==(modInt other) {
		return val == other.val;
	}

	bool operator!=(modInt other) {
		return val != other.val;
	}

	friend ostream& operator<<(ostream& os, modInt v) {
		os << v.val;
		return os;
	}

	friend istream& operator>>(istream& is, modInt& v) {
		i64 x;
		is >> x;
		v.val = (x % m + m) % m; 
		return is;
	}

	friend modInt operator+(i64 x, modInt other) {
		return other + x;
	}

	friend modInt operator-(i64 x, modInt other) {
		return modInt{x} - other;
	}

	friend modInt operator*(i64 x, modInt other) {
		return other * x;
	}

	friend modInt operator/(i64 x, modInt other) {
		return modInt{x} / other;
	}
};

const int MOD = 998244353;

using modint = modInt<MOD>;

struct op {
	int operator()(int a, int b) {
		return a + b;
	}
};

template<class T, class op>
struct BIT {
	vector<T> bit;
	static const T neutral;

	BIT() {}

	BIT(int n) {
		bit.assign(n + 1, neutral);
	}
	
	void upd(int k, T x) {	
		for(++k; k < int(bit.size()); k += k & -k) bit[k] = op()(bit[k], x);
	}
	
	T query(int k) {
		T ans = neutral;
		for(++k; k > 0; k -= k & -k) ans = op()(ans, bit[k]);
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return neutral;
		return op()(query(r), -query(l - 1));
	}
};

template<class T, class op>
const T BIT<T, op> :: neutral = 0;

void solve() {
	int n;

	cin >> n;

	vector<ii> p(n);
	modint cnt;
	vector<int> coords;

	for(auto& [x, y] : p) {
		cin >> x >> y;
		cnt += (modint{2}^n) - 1;
		coords.pb(x);
	}

	sort(all(p));
	sort(all(coords));

	auto lb = [&](int y) {
		return lower_bound(all(coords), y) - coords.begin();
	};

	for(int i = 0; i < n; ++i) {
		cnt -= (modint{2}^i) - 1;
		cnt -= (modint{2}^(n-i-1)) - 1;
	}

	for(auto& [x, y] : p) swap(x, y);

	sort(all(p));

	for(int i = 0; i < n; ++i) {
		cnt -= (modint{2}^i) - 1;
		cnt -= (modint{2}^(n-i-1)) - 1;
	}

	for(int i = 0; i < 2; ++i) {
		BIT<int, op> bit(n);
		for(int j = 0; j < n; ++j) {
			int k = lb(p[j].sc);
			int m = bit.query(k);
			cnt += (modint{2}^m) - 1;
			cnt += (modint{2}^(j - m)) - 1;
			bit.upd(k, 1);
		}
		reverse(all(p));
	}

	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
