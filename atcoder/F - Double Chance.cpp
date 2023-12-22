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

const int MOD = 998244353;

struct op {
	int operator()(int a, int b) {
		return (a + b) % MOD;
	}
};

template<class T, class op>
struct BIT {
	vector<T> bit;
	T def;

	BIT(int n, T _def = 0) : def {_def} {
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

i64 exp(i64 n, int p, int m) {
	i64 ans = 1;
	n %= m;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % m;
		n = n * n % m;
	}
	return ans;
}

void solve() {

	int n;

	cin >> n;

	vector<int> a(n);

	for(int& v : a) cin >> v;

	const int MAXN = 2e5 + 1;
	BIT<int, op> cnt(MAXN, 0), sum(MAXN, 0);
	vector<i64> ps(n + 1, 0);

	for(int i = 1; i <= n; ++i) {

		ps[i] = (ps[i] + ps[i - 1]) % MOD;
		ps[i] = (ps[i] + 2ll * cnt.query(a[i - 1]) * a[i - 1]) % MOD;
		ps[i] = (ps[i] + 2 * sum.query(a[i - 1] + 1, MAXN - 1)) % MOD;
		ps[i] = (ps[i] + a[i - 1]) % MOD;

		i64 k = exp(1ll * i * i, MOD - 2, MOD);
		cout << (ps[i] * k % MOD  + MOD) % MOD << '\n';

		cnt.upd(a[i - 1], 1);
		sum.upd(a[i - 1], a[i - 1]);
	}
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
