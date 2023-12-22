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

	modInt operator^(i64 p) {
		return {int(exp(val, p, m))};
	}
	
	modInt operator^=(i64 p) {
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
	
	modInt operator+=(modInt x) {
		val += x.val;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt operator-=(modInt x) {
		val -= x.val;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(modInt x) {
		return {int(((i64)val * x.val % m + m) % m)};
	}

	modInt operator*=(modInt x) {
		val = ((i64)val * x.val % m + m) % m;
		return *this;
	}
	
	modInt operator/(modInt x) {
		return {int((val * exp(x.val, m - 2, m) % m + m) % m)};
	}
	
	modInt operator/=(modInt x) {
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
	
	modInt operator+=(i64 x) {
		x = (x % m + m) % m;
		val += x;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt operator-=(i64 x) {
		x = (x % m + m) % m;
		val -= x;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(i64 x) {
		x = (x % m + m) % m;
		return {int((i64)val * x % m)};
	}
	
	modInt operator*=(i64 x) {
		x = (x % m + m) % m;
		val = (i64)val * x % m;
		return *this;
	}
	
	modInt operator/(i64 x) {
		return {int(val * exp(x, m - 2, m) % m)};
	}
	
	modInt operator/=(i64 x) {
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

void solve() {
	int n, l;

	cin >> n >> l;

	const int MOD = 998244353;
	using modint = modInt<MOD>;

	vector<bool> have(1<<26, 0);	
	vector<int> frq(27, 0);
	modint C[27][27];

	for(int i = 0; i <= 26; ++i) {
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; ++j)
			C[i][j] = C[i-1][j]+C[i-1][j-1];
	}

	for(int i = 0; i < n; ++i) {
		int mask = 0;
		string s;
		cin >> s;
		for(char c : s) mask |= 1 << (c - 'a');
		have[mask] = true;
	}

	for(int i = (1<<26)-1; i >= 0; --i) {
		if(!have[i]) continue;
		for(int j = i; j; j -= j & -j) have[i ^ (j & -j)] = true;
		++frq[__builtin_popcount(i)];
	}

	modint ans;

	for(int i = 1; i <= 26; ++i) {
		modint k = modint(i)^l;
		for(int j = i - 1; j; --j)
			k += ((i-j) % 2 ? -1 : 1) * C[i][j] * (modint(j)^l);
		k *= frq[i];
		ans += k;
	}

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
