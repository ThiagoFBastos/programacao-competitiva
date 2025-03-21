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

const int N = 1e6 + 100, MOD = 1e9 + 7;

modInt<MOD> fat[N], inv[N], invf[N], pt3[N];

auto C(int n, int k) {
	return fat[n] * invf[n - k] * invf[k];
}

void solve() {

	int n, k;

	cin >> n >> k;

	pt3[0] = 1;
	for(int i = 1; i <= n; ++i) pt3[i] = pt3[i - 1] * 3;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;

	for(int i = 2; i <= n; ++i) {
		fat[i] = fat[i - 1] * i;
		inv[i] = inv[MOD % i] * (MOD - MOD / i);
		invf[i] = invf[i - 1] * inv[i];
	}

	if(k == 0) {
		cout << pt3[n] << '\n';
		return;
	}

	modInt<MOD> ans;


	for(int b = 1; b <= n; ++b) {
				
		// com 0
		int zeroes = n - k - b;
		int ones = k - b;

		if(zeroes >= 0 && ones >= 0)
			ans += C(zeroes + b, b) * C(ones + b - 1, b - 1) * pt3[ones] * pt3[zeroes];			

		// sem 0

		zeroes = n - k - (b - 1);
		ones = k - b;

		if(zeroes >= 0 && ones >= 0)
			ans += C(zeroes + b - 1, b - 1) * C(ones + b - 1, b - 1) * pt3[ones] * pt3[zeroes];	
	}

	cout << ans << '\n';
}	

int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}


