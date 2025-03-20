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
	modInt(int val) : val {val} {}
	
	modInt operator^(i64 p) {
		return {int(exp(val, p, m))};
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

const int MOD = 1e9 + 7, N = 1e2 + 10;

using modint = modInt<MOD>;

modint dp[2][N];

void solve() {
	int n, pi, pj, x, y;
	modint cnt;

	cin >> n >> pi >> pj >> x >> y;

	for(int i = 1; i <= n; ++i) dp[0][i] = 0;

	dp[0][1] = 1;

	for(int i = 1; i <= n; ++i) {

		for(int l = 1; l <= n; ++l) dp[1][l] = 0;

		if(i == x) {
			for(int l = 1; l <= i; ++l) {
				int r = n - i + l;
				if(l > r) continue;
				if(l == pi && !(l == 1 && i == n)) dp[1][l + 1] += dp[0][l];
				if(l != r && r == pi && !(r == n && i == n)) dp[1][l] += dp[0][l];
			}
		} else if(i == y) {
			for(int l = 1; l <= i; ++l) {
				int r = n - i + l;
				if(l > r) continue;
				if(l == pj && !(l == 1 && i == n)) dp[1][l + 1] += dp[0][l];
				if(l != r && r == pj && !(r == n && i == n)) dp[1][l] += dp[0][l];
			}
		} else {
			for(int l = 1; l <= i; ++l) {
				int r = n - i + l;
				if(l > r || (i == n && l == 1)) continue;
				if(l != pi && l != pj && !(l == 1 && i == n)) dp[1][l + 1] += dp[0][l];
				if(l != r && r != pi && r != pj && !(r == n && i == n)) dp[1][l] += dp[0][l];
			}
		}

		for(int i = 1; i <= n; ++i) dp[0][i] = dp[1][i];
	}

	for(int i = 1; i <= n; ++i) cnt += dp[0][i];

	cout << cnt << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

