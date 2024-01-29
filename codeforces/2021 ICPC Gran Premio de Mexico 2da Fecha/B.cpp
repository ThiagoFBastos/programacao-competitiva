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

const int N = 1e5 + 10, MOD = 998244353;

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
	modInt(int val) : val {val} {}
	
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

	friend ostream& operator<<(ostream& os, modInt<m> v) {
		os << v.val;
		return os;
	}

	friend istream& operator>>(istream& is, modInt<m>& v) {
		is >> v.val;
		return is;
	}
};

using modint = modInt<MOD>;

modint fat[N], inv[N], invf[N], ps[N], pw[2][N];

modint C(int n, int k) {
	return fat[n] * invf[k] * invf[n - k];
}

void solve() {
	int n, m;

	cin >> n >> m;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;

	for(int i = 2; i <= m; ++i) {
		fat[i] = fat[i - 1] * i;
		inv[i] = inv[MOD % i] * (MOD - MOD / i);
		invf[i] = inv[i] * invf[i - 1];
	}
	
	auto k = modint{1} / n;

	pw[0][0] = pw[1][0] = 1;

	for(int i = 1; i <= m; ++i) {
		pw[0][i] = pw[0][i - 1] * (n - 1);
		pw[1][i] = pw[1][i - 1] * k;
	}

	for(int i = 0; i <= m; ++i) {
		modint f = C(m, i) * pw[0][m - i] * pw[1][m];
		ps[i + 1] = ps[i] + f;
	}

	modint e[10];

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		for(int p = 1; p <= 1e5; p *= 10) {
			for(int d = 1; d <= 9; ++d) {
				int L = max(a, d * p), R = d * p + p - 1;
				if(L > R || L - a > m) continue;
				e[d] += ps[min(m, R - a) + 1] - ps[L - a];
			}
		}
	}

	for(int d = 1; d <= 9; ++d) cout << e[d] << '\n';
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

