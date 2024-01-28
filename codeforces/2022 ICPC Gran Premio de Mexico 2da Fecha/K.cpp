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

const int N = 1e5 + 10, MOD = 1e9 + 7;

struct node {
	int lin_sum;
	int sqr_sum;
	int lazy_lin_sum;
	int lazy_sqr_sum;
	bool prop;
	node() {}
	node(int x) {
		lin_sum = x;
		sqr_sum = (i64)x * x % MOD;
		lazy_lin_sum = lazy_sqr_sum = 0;
		prop = false;
	}
};

node st[4 * N];
int n, q, a[N];

void combine(int p) {
	st[p].lin_sum = (st[2 * p].lin_sum + st[2 * p + 1].lin_sum) % MOD;
	st[p].sqr_sum = (st[2 * p].sqr_sum + st[2 * p + 1].sqr_sum) % MOD;
}

void build(int l, int r, int p = 1) {
	if(l == r) {
		st[p] = node(a[l]);
		return;
	}
	int m = (l + r) / 2;
	build(l, m, 2 * p);
	build(m + 1, r, 2 * p + 1);
	combine(p);	
}

void apply(int p, int a, int b, int n) {
	st[p].sqr_sum = (st[p].sqr_sum + 2ll * st[p].lin_sum * a + (i64)b * n) % MOD;
	st[p].lin_sum = (st[p].lin_sum + (i64)a * n) % MOD;
	st[p].prop = true;
	st[p].lazy_sqr_sum = (st[p].lazy_sqr_sum + b + 2ll * st[p].lazy_lin_sum * a) % MOD;
	st[p].lazy_lin_sum = (st[p].lazy_lin_sum + a) % MOD;
}

void propagate(int p, int n) {
	if(!st[p].prop) return;
	apply(2 * p, st[p].lazy_lin_sum, st[p].lazy_sqr_sum, (n + 1) / 2);
	apply(2 * p + 1, st[p].lazy_lin_sum, st[p].lazy_sqr_sum, n / 2);
	st[p].prop = false;
	st[p].lazy_lin_sum = 0;
	st[p].lazy_sqr_sum = 0;
}

void upd(int l, int r, int x, int lo, int hi, int p = 1) {
	if(l > r || r < lo || hi < l) return;
	else if(lo >= l && hi <= r) {
		apply(p, x, (i64)x * x % MOD, hi - lo + 1);
		return;
	}
	int m = (lo + hi) / 2;
	propagate(p, hi - lo + 1);
	upd(l, r, x, lo, m, 2 * p);
	upd(l, r, x, m + 1, hi, 2 * p + 1);
	combine(p);
}

int query(int l, int r, int lo, int hi, int p = 1) {
	if(l > r || r < lo || hi < l) return 0;
	else if(lo >= l && hi <= r) return st[p].sqr_sum;
	int m = (lo + hi) / 2;
	propagate(p, hi - lo + 1);
	int a = query(l, r, lo, m, 2 * p);
	int b = query(l, r, m + 1, hi, 2 * p + 1);
	return (a + b) % MOD;
}

void solve() {
	cin >> n >> q;

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		a[i] = (a[i] + MOD) % MOD;
	}

	build(0, n - 1);

	while(q--) {
		char t;
		int l, r, x;
		cin >> t >> l >> r;
		--l, --r;
		if(t == 'u') {
			cin >> x;
			x = (x + MOD) % MOD;
			upd(l, r, x, 0, n - 1);
		} else
			cout << query(l, r, 0, n - 1) << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

