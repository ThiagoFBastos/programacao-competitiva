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

const int N = 6e4 + 10;

int a[N], n, nxt[N], last[N];

struct Node {
	double sum;
	double pre;
};

double v[N];
Node st[4 * N];

Node merge(Node l, Node r) {
	Node p;
	p.sum = l.sum + r.sum;
	p.pre = min(l.pre, l.sum + r.pre);
	return p;
}

void build(int l, int r, int p = 1) {
	if(l == r) {st[p] = {v[l], v[l]}; return;}
	int m = (l + r) / 2;
	build(l, m, 2 * p);
	build(m + 1, r, 2 * p + 1);
	st[p] = merge(st[2 * p], st[2 * p + 1]);
}

void upd(int k, double x, int l, int r, int p = 1) {
	if(l == r) {st[p] = {x, x}; return;}
	int m = (l + r) / 2;
	if(k <= m) upd(k, x, l, m, 2 * p);
	else upd(k, x, m + 1, r, 2 * p + 1);
	st[p] = merge(st[2 * p], st[2 * p + 1]);
}

Node query(int l, int r, int lo, int hi, int p = 1) {
	if(lo >= l && hi <= r) return st[p];
	int m = (lo + hi) / 2;
	if(l <= m && m < r) return merge(query(l, r, lo, m, 2 * p), query(l, r, m + 1, hi, 2 * p + 1));
	else if(r <= m) return query(l, r, lo, m, 2 * p);
	return query(l, r, m + 1, hi, 2 * p + 1);
}

bool evaluate(double cte) {
	double best = INF;
	for(int i = 1; i <= n; ++i) last[i] = -1;
	for(int i = 0; i < n; ++i) {
		nxt[i] = -1;
		if(last[a[i]] != -1) v[i] = -cte, nxt[last[a[i]]] = i;
		else v[i] = 1 - cte;
		last[a[i]] = i;
	}
	build(0, n - 1);
	for(int i = 0; i < n; ++i) {
		auto ans = query(i, n - 1, 0, n - 1);
		best = min(best, ans.pre);
		if(nxt[i] != -1) upd(nxt[i], 1 - cte, 0, n - 1);
	}
	return best <= 0;
}

void solve() {
	cin >> n;

	for(int i = 0; i < n; ++i) cin >> a[i];

	double l = 0, r = 1;

	while(fabs(r - l) > EPS) {
		double m = (l + r) / 2;
		if(evaluate(m)) r = m;
		else l = m;
	}

	cout << fixed << setprecision(9) << r << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}