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

const int MOD = 1e9 + 7;

using modint = modInt<MOD>;

void solve() {
	int n;

	cin >> n;

	vector<vector<int>> adj(n);
	vector<int> sz(n);
	modint e;

	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	auto dfs = [&](auto& dfs, int u, int p)->void {
		modint P[3];
		P[0] = 1;
		sz[u] = 1;
		for(int v : adj[u]) {
			if(v == p) continue;
			modint tmp[3];
			dfs(dfs, v, u);
			sz[u] += sz[v];
			modint p0 = 1 / (modint{2}^sz[v]), p1 = (1 - 1 / (modint{2}^sz[v]));
			tmp[0] = P[0] * p0;
			tmp[1] = P[1] * p0 + P[0] * p1;
			tmp[2] = P[2] + P[1] * p1;
			P[0] = tmp[0], P[1] = tmp[1], P[2] = tmp[2];
		}
		if(p != -1) {
			int m = n - sz[u];
			modint p0 = 1 / (modint{2}^m), p1 = (1 - 1 / (modint{2}^m));
			modint tmp[3];
			tmp[0] = P[0] * p0;
			tmp[1] = P[1] * p0 + P[0] * p1;
			tmp[2] = P[2] + P[1] * p1;
			P[0] = tmp[0], P[1] = tmp[1], P[2] = tmp[2];
		}
		e += P[2] / 2;
	};

	dfs(dfs, 0, -1);

	cout << e << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
