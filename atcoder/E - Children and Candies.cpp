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

const int N = 410, MOD = 1e9 + 7;

template<int m>
struct modInt {
	int val;
	
	modInt() {val = 0;}
	modInt(int val) : val {val} {}
	
	i64 exp(i64 n, int p) {
		i64 ans = 1;
		for(; p > 0; p >>= 1) {
			if(p & 1) ans = ans * n % m;
			n = n * n % m;
		}
		return ans;
	}
	
	modInt operator^(int p) {
		return modInt(exp(val, p));
	}
	
	modInt& operator^=(int p) {
		val = exp(val, p);
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
		return modInt((i64)val * x.val % m);
	}

	modInt& operator*=(modInt x) {
		val = (i64)val * x.val % m;
		return *this;
	}
	
	modInt operator/(modInt x) {
		return modInt(val * exp(x.val, m - 2) % m);
	}
	
	modInt& operator/=(modInt x) {
		val = val * exp(x.val, m - 2) % m;
		return *this;
	}
	
	modInt operator+(int x) {
		int ans = val + x;
		if(ans >= m) ans -= m;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt operator-(int x) {
		int ans = val - x;
		if(ans < 0) ans += m;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt& operator+=(int x) {
		val += x;
		if(val >= m) val -= m;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt& operator-=(int x) {
		val -= x;
		if(val < 0) val += m;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt operator*(int x) {
		i64 ans = (i64)val * x % m;
		if(ans < 0) ans += m;
		return modInt(ans);
	}
	
	modInt& operator*=(int x) {
		val = (i64)val * x % m;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator/(int x) {
		return modInt(val * exp(x, m - 2) % m);
	}
	
	modInt& operator/=(int x) {
		val = val * exp(x, m - 2) % m;
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

modInt<MOD> pt[N][N];

void solve() {
	int n, c;

	cin >> n >> c;

	for(int i = 1; i < N; ++i) {
		pt[i][0] = 1;
		for(int j = 1; j < N; ++j) pt[i][j] = pt[i][j - 1] * i;
	}

	vector<int> a(n), b(n);

	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;

	vector<modInt<MOD>> dp(c + 1, 0);
	dp[0] = 1;

	for(int i = 0; i < n; ++i) {
		vector<modInt<MOD>> x(c + 1, 0), cp(c + 1, 0);
		
		for(int k = 0; k <= c; ++k)
			for(int l = a[i]; l <= b[i]; ++l)
				x[k] += pt[l][k];
		
		for(int j = c; j >= 0; --j)
			for(int k = 0; k + j <= c; ++k)
				cp[k + j] += dp[j] * x[k];

		swap(cp, dp);
	}

	cout << dp[c] << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
