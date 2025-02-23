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

template<int m>
struct modInt {
	
	int val;
	
	i64 exp(i64 n, i64 p) {
		i64 ans = 1;
		n %= m;
		for(; p > 0; p >>= 1) {
			if(p & 1) ans = ans * n % m;
			n = n * n % m;
		}
		return ans;
	}

	modInt() {val = 0;}
	modInt(int v) : val {v + m * (v < 0) - m * (v >= m)} {}

	modInt operator-() {return {-val};}
	modInt operator^(i64 p) {return {exp(val, p)};}
	modInt& operator^=(i64 p) {return *this = *this^p;}
	modInt operator+(const modInt& x) const {int ans = val + x.val;return {ans};}
	modInt operator-(const modInt& x) const {int ans = val - x.val;return {ans};}
	modInt& operator+=(const modInt& x) {return *this = *this + x;}
	modInt& operator-=(const modInt& x) {return *this = *this - x;}
	modInt operator*(const modInt& x) const {return {int((i64)val * x.val % m)};}
	modInt& operator*=(const modInt& x) {return *this = *this * x;}
	modInt operator/(const modInt& x) const {return {int(val * exp(x.val, m - 2) % m)};}
	modInt& operator/=(const modInt& x) {return *this = *this / x;}
	modInt operator+(i64 x) {return {int((val + x) % m)};}
	modInt operator-(i64 x) {return {int((val - x) % m)};}
	modInt& operator+=(i64 x) {return *this = *this + x;}
	modInt& operator-=(i64 x) {return *this = *this - x;}
	modInt operator*(i64 x) {return {int(x % m * val % m)};}
	modInt& operator*=(i64 x) {return *this = *this * x;}
	modInt operator/(i64 x) {return {int(val * exp(x, m - 2, m) % m)};}
	modInt& operator/=(i64 x) {return *this = *this / x;}
	bool operator==(const modInt& other) {return val == other.val;}
	bool operator!=(const modInt& other) {return val != other.val;}
	friend ostream& operator<<(ostream& os, const modInt& v) {os << v.val; return os;}
	friend istream& operator>>(istream& is, modInt& v) {is >> v.val; return is;}
	friend modInt operator+(i64 v, const modInt& u) {return u + v;}
	friend modInt operator-(i64 v, const modInt& u) {return modInt(v) - u;}
	friend modInt operator*(i64 v, const modInt& u) {return u * v;}
	friend modInt operator/(i64 v, const modInt& u) {return modInt(v) / u;}
};

bool lucky(int x) {
	while(x > 0) {
		int d = x % 10;
		if(d != 4 && d != 7) return false;
		x /= 10;
	}
	return true;
}

const int MOD = 1e9 + 7;

using modint = modInt<MOD>;

void solve() {
	int n, k;

	cin >> n >> k;

	map<int, int> mp;
	int unlucky = 0;
	vector<modint> dp(k + 1, 0), fat(n + 1), inv(n + 1), invf(n + 1);
	modint cnt;

	dp[0] = 1;

	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		if(lucky(v)) ++mp[v];
		else ++unlucky;
	}
	
	for(auto [x, y] : mp)
		for(int i = k - 1; i >= 0; --i)
			dp[i + 1] += y * dp[i];

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;

	for(int i = 2; i <= n; ++i) {
		fat[i] = i * fat[i - 1];
		inv[i] = inv[MOD % i] * (MOD - MOD / i);
		invf[i] = invf[i - 1] * inv[i];
	}

	auto C = [&](int n, int k)->modint {
		return fat[n] * invf[k] * invf[n - k];
	};

	for(int i = 0; i <= k; ++i) {
		if(unlucky < k - i) continue;
		cnt += C(unlucky, k - i) * dp[i];
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