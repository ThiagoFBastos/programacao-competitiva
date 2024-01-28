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

const int MOD = 515011997, N = 18002 + 10;

using modint = modInt<MOD>;

modint fat[N], inv[N], invf[N];
array<modint, N> dp[2];

modint P(int frq[26]) {
	int n = accumulate(frq, frq + 26, 0);
	modint cnt = fat[n];
	for(int k = 0; k < 26; ++k) cnt = cnt * invf[frq[k]];
	return cnt;
}

void solve() {
	int n, m, c = 0, frq[26] = {0};
	string s;
	modint cnt, invalid;

	cin >> n >> m >> s;

	if(n > m) swap(n, m);

	for(char c : s) ++frq[c - 'a'];

	for(int i = 0; i < 26; ++i) c += !!frq[i];

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;

	for(int i = 2; i <= n + m; ++i) {
		fat[i] = fat[i - 1] * i;
		inv[i] = inv[MOD % i] * (MOD - MOD / i);
		invf[i] = invf[i - 1] * inv[i];
	}

	for(int i = 0; i <= n; ++i) dp[0][i] = 0;

	dp[0][0] = fat[n] * fat[m] / n / m;

	for(int i = 0; i < 26; ++i) {
		if(!frq[i]) continue;

		for(int j = 0; j < 2; ++j) {
			if(frq[i] >= n && c - (frq[i] == n) > 1) {
				frq[i] -= n;
				auto t = P(frq);
				cnt += t / m;
				invalid += t;
				frq[i] += n;
			}
			swap(n, m);
		}

		if(frq[i] >= n) {
			frq[i] -= n;
			for(int j = 0; j < 26; ++j) {
				if(frq[j] != m) continue;
				cnt += 1;
				invalid += 1;
			}
			frq[i] += n;
		}

		for(int j = 0; j <= n; ++j) dp[1][j] = 0;

		for(int j = n; j >= 0; --j) {
			int l = min(n - j, frq[i]);
			for(int k = 0; k <= l; ++k) dp[1][k + j] += dp[0][j] * invf[k] * invf[frq[i] - k];
		}

		swap(dp[0], dp[1]);
	}

	invalid = invalid / n / m;
	
	cout << cnt + dp[0][n] - invalid << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}


