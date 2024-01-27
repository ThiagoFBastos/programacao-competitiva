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

const int N = 2e5 + 10, K = 19;

struct node {
	int maxv;
	int minv;
	int best;
};

node st[4 * N], sp[K][2 * N];
int n, q, a[N], b[2 * N], lz[4 * N];

node merge(node a, node b) {
	node c;
	c.maxv = max(a.maxv, b.maxv);
	c.minv = min(a.minv, b.minv);
	c.best = max(max(a.best, b.best), b.maxv - a.minv);
	return c;
}

node query(int l, int r) {
	int d = r - l + 1;
	node ans = {-INF, INF, 0};
	for(; d; d -= d & -d) {
		int i = __builtin_ctz(d);
		ans = merge(ans, sp[i][l]);
		l += 1 << i;
	}
	return ans;
}

void build(int l, int r, int p = 1) {
	lz[p] = -1;
	if(l == r) {
		st[p] = {a[l], a[l], 0};
		return;
	}
	int m = (l + r) / 2;
	build(l, m, 2 * p);
	build(m + 1, r, 2 * p + 1);
	st[p] = merge(st[2 * p], st[2 * p + 1]);
}

void propagate(int p, int n) {
	if(lz[p] < 0) return;
	int m = (n + 1) / 2;
	lz[2 * p] = lz[p];
	lz[2 * p + 1] = lz[p] + m;
	st[2 * p] = query(lz[p], lz[p] + m - 1);
	st[2 * p + 1] = query(lz[p] + m, lz[p] + n - 1);
	lz[p] = -1;
}

void upd(int l, int r, int k, int lo, int hi, int p = 1) {
	if(lo >= l && hi <= r) {
		st[p] = query(k, k + hi - lo);
		lz[p] = k;
		return;
	}
	int m = (lo + hi) / 2;
	propagate(p, hi - lo + 1);
	if(r <= m) upd(l, r, k, lo, m, 2 * p);
	else if(l > m) upd(l, r, k, m + 1, hi, 2 * p + 1);
	else {
		upd(l, m, k, lo, m, 2 * p);
		upd(m + 1, r, k + m - l + 1, m + 1, hi, 2 * p + 1);
	}
	st[p] = merge(st[2 * p], st[2 * p + 1]);
}

node get(int l, int r, int lo, int hi, int p = 1) {
	if(lo >= l && hi <= r) return st[p];
	int m = (lo + hi) / 2;
	propagate(p, hi - lo + 1);
	if(r <= m) return get(l, r, lo, m, 2 * p);
	else if(l > m) return get(l, r, m + 1, hi, 2 * p + 1);
	node a = get(l, r, lo, m, 2 * p);
	node b = get(l, r, m + 1, hi, 2 * p + 1);
	return merge(a, b);
}

void solve() {
	cin >> n >> q;

	for(int i = 0; i < n; ++i) cin >> a[i];

	for(int i = 0; i < n; ++i) {
		cin >> b[i];
		b[i + n] = b[i];
	}

	int lg = 32 - __builtin_clz(2 * n);
	for(int i = 0; i < 2 * n; ++i) sp[0][i] = {b[i], b[i], 0};

	for(int i = 1; i < lg; ++i)
		for(int j = 0; j + (1 << i) <= 2 * n; ++j)
			sp[i][j] = merge(sp[i-1][j],sp[i-1][j+(1<<(i-1))]);

	build(0, n - 1);

	while(q--) {
		int t, l, r, k;
		cin >> t >> l >> r;
		if(t == 1) {
			cin >> k;
			upd(l, r, k, 0, n - 1);
			cout << st[1].best << '\n';
		} else {
			node a = get(l, r, 0, n - 1);
			cout << a.best << '\n';
		}
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

