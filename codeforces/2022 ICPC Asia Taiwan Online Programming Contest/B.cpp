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

const int N = 1e5 + 10;

i64 sum[4 * N], sumprod[4 * N], lz[4 * N];
int mark[4 * N], a[N], n, q;

void refresh(int p) {
	sum[p] = sum[2 * p] + sum[2 * p + 1];
	sumprod[p] = sumprod[2 * p] + sumprod[2 * p + 1];
}

void build(int l, int r, int p = 1) {
	if(l == r) {
		sum[p] = a[l];
		sumprod[p] = (i64)a[l] * l;
	} else {
		int m = (l + r) / 2;
		build(l, m, 2 * p);
		build(m + 1, r, 2 * p + 1);
		refresh(p);
	}
}

void applyUPD(int p, int lo, int hi, i64 x) {
	i64 s = (hi - lo + 1ll) * (lo + hi) / 2;
	sum[p] += (hi - lo + 1ll) * x;
	sumprod[p] += x * s;
	lz[p] += x;
	mark[p] = mark[p] == 1 ? 1 : 0;
}

void applyChange(int p, int lo, int hi, i64 x) {
	i64 s = (hi - lo + 1ll) * (lo + hi) / 2;
	sum[p] = (hi - lo + 1ll) * x;
	sumprod[p] = x * s;
	lz[p] = x;
	mark[p] = 1;
}

void push(int p, int l, int r) {
	if(mark[p] < 0) return;
	int m = (l + r) / 2;
	int I[2][2] = {{l, m}, {m + 1, r}};
	int k[2] = {2 * p, 2 * p + 1};
	for(int i : {0, 1}) {
		if(mark[p] == 0) applyUPD(k[i], I[i][0], I[i][1], lz[p]);
		else applyChange(k[i], I[i][0], I[i][1], lz[p]);
	}
	lz[p] = 0;
	mark[p] = -1;
}

void upd(int l, int r, int x, int lo, int hi, int p = 1) {
	if(l > r || r < lo || l > hi) return;
	else if(lo >= l && hi <= r) applyUPD(p, lo, hi, x);
	else {
		int m = (lo + hi) / 2;
		push(p, lo, hi);
		upd(l, r, x, lo, m, 2 * p);
		upd(l, r, x, m + 1, hi, 2 * p + 1);
		refresh(p);
	}
}

void change(int l, int r, int x, int lo, int hi, int p = 1) {
	if(l > r || r < lo || l > hi) return;
	else if(lo >= l && hi <= r) applyChange(p, lo, hi, x);
	else {
		int m = (lo + hi) / 2;
		push(p, lo, hi);
		change(l, r, x, lo, m, 2 * p);
		change(l, r, x, m + 1, hi, 2 * p + 1);
		refresh(p);
	}
}

i64 query_sum(int l, int r, int lo, int hi, int p = 1) {
	if(l > r || r < lo || l > hi) return 0;
	else if(lo >= l && hi <= r) return sum[p];
	int m = (lo + hi) / 2;
	push(p, lo, hi);
	i64 a = query_sum(l, r, lo, m, 2 * p);
	i64 b = query_sum(l, r, m + 1, hi, 2 * p + 1);
	return a + b;
}

i64 query_sum_prod(int l, int r, int lo, int hi, int p = 1) {
	if(l > r || r < lo || l > hi) return 0;
	else if(lo >= l && hi <= r) return sumprod[p];
	int m = (lo + hi) / 2;
	push(p, lo, hi);
	i64 a = query_sum_prod(l, r, lo, m, 2 * p);
	i64 b = query_sum_prod(l, r, m + 1, hi, 2 * p + 1);
	return a + b;
}

void solve() {
	cin >> n >> q;

	for(int i = 1; i <= n; ++i) cin >> a[i];

	build(1, n);
	
	while(q--) {
		int t, l, r, x;
		cin >> t >> l >> r;
		if(t == 1) {
			cin >> x;
			upd(l, r, x, 1, n);
		} else if(t == 2) {
			cin >> x;
			change(l, r, x, 1, n);
		} else {
			i64 s = query_sum(l, r, 1, n);
			i64 sp = query_sum_prod(l, r, 1, n) - s * (l - 1);
			if(sp == 0 && s == 0) cout << "Yes\n";
			else if(s == 0 || sp % s || sp / s <= 0 || sp / s > r - l + 1) cout << "No\n";
			else cout << "Yes\n";
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

