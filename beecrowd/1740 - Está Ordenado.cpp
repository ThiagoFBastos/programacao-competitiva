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
//using i128 = __int128;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<i64> uid(0ll, 1ll<<62);

struct node {
	int key;
	int val;
	bool f[3][2];
	i64 pry;
	int l, r;
	int prv;
};

const int N = 2e5;

node p[N];
int root, nd, inv[N];

int newnode(int _val, bool _equal, bool _incr, bool _decr, int _key = 1) {
	node& u = p[nd++];
	u.key = _key;
	u.val = _val;
	u.f[0][1] = u.f[0][0] = _equal;
	u.f[1][1] = u.f[1][0] = _incr;
	u.f[2][1] = u.f[2][0] = _decr;
	u.pry = uid(rng);
	u.l = u.r = 0;
	u.prv = 0;
	return nd - 1;
}

void refresh(int t) {
	if(t == 0) return;
	node &u = p[t], &l = p[u.l], &r = p[u.r];
	u.key = 1 + l.key + r.key;
	for(int i = 0; i < 3; ++i)
		u.f[i][1] = u.f[i][0] && l.f[i][1] && r.f[i][1];
}

void split(int t, int k, int& L, int& R) {
	refresh(t);
	if(t == 0) {L = R = 0; return;}
	if(p[p[t].l].key + 1 <= k) {
		split(p[t].r, k - p[p[t].l].key - 1, p[t].r, R);
		L = t;
	} else {
		split(p[t].l, k, L, p[t].l);
		R = t;
	}
	refresh(t);
}

int merge(int t1, int t2) {
	refresh(t1);
	refresh(t2);
	if(t1 == 0 || t2 == 0) return t2 != 0 ? t2 : t1;
	if(p[t1].pry < p[t2].pry) {
		p[t2].l = merge(t1, p[t2].l);
		refresh(t2);
		return t2;
	}
	p[t1].r = merge(p[t1].r, t2);
	refresh(t1);
	return t1;
}

void heapfy(int t) {
	if(t == 0) return;
	int u = t;
	if(p[t].l != 0 && p[p[t].l].pry > p[u].pry) u = p[t].l;
	if(p[t].r != 0 && p[p[t].r].pry > p[u].pry) u = p[t].r;
	if(u != t) {
		swap(p[t].pry, p[u].pry);
		heapfy(u);
	}
}

int build(vector<int>& a, int lo, int hi) {
	if(lo > hi) return 0;
	int m = (lo + hi) / 2;
	inv[m] = newnode(a[m], m&&a[m - 1]==a[m], m&&a[m-1]<=a[m],m&&a[m-1]>=a[m]);
	p[inv[m]].l = build(a, lo, m - 1);
	p[inv[m]].r = build(a, m + 1, hi);
	if(m) p[inv[m]].prv = inv[m - 1];
	refresh(inv[m]);
	heapfy(inv[m]);
	return inv[m];
}

void build(vector<int>& a) {
	nd = 0;
	newnode(0, true, true, true, 0);
	root = build(a, 0, (int)a.size() - 1);
}

int query(int l, int r) {	
	int a, b, c, ans;
	split(root, l, a, b);
	split(b, r - l, b, c);
	if(p[b].f[0][1]) ans = 0;
	else if(p[b].f[1][1]) ans = 1;
	else if(p[b].f[2][1]) ans = 2;
	else ans = 3;
	root = merge(a, merge(b, c));
	return ans;
}

int find(int k) {
	int a, b, c;
	split(root, k - 1, a, b);
	split(b, 1, b, c);
	root = merge(a, merge(b, c));
	return b;
}

void fix(int k) {
	auto fixit = [&](auto&& fixit, int t, int k) -> void {
		if(!t) return;
		else if(p[p[t].l].key + 1 == k) {
			node &A = p[t];
			node &B = p[A.prv];
			A.f[0][0] = A.prv && A.val == B.val;
			A.f[1][0] = A.prv && B.val <= A.val;
			A.f[2][0] = A.prv && B.val >= A.val;
		} else if(p[p[t].l].key + 1 > k) fixit(fixit, p[t].l, k);
		else fixit(fixit, p[t].r, k - p[p[t].l].key - 1);
		refresh(t);
	};
	fixit(fixit, root, k);
}

void swap_places(int i, int j) {
	if(i > j) swap(i, j);
	int a = find(i), b = find(j);
	swap(p[a].val, p[b].val);
	fix(i); fix(i + 1); fix(j); fix(j + 1);
}

void add(int k, int v) {
	int a, b, c = newnode(v, 0, 0, 0);
	split(root, k - 1, a, b);
	root = merge(merge(a, c), b);
	if(int d = find(k + 1); d) p[d].prv = c;
	p[c].prv = find(k - 1);
	fix(k); fix(k + 1);
}

void upd(int k, int v) {
	int a = find(k);
	p[a].val = v;
	fix(k); fix(k + 1);
}

void rem(int k) {
	int a, b, c;
	split(root, k - 1, a, b);
	split(b, 1, b, c);
	root = merge(a, c);
	if(int d = find(k); d) p[d].prv = p[b].prv;	
	fix(k);
}

string info[] = {"ALL EQUAL", "NON DECREASING", "NON INCREASING", "NONE"};

void solve() {
	int n, q;
	while(cin >> n) {
		vector<int> a(n);
		for(int& v : a) cin >> v;
		build(a);
		cin >> q;
		while(q--) {
			int t, x, y;
			cin >> t >> x;
			if(t == 0) {cin >> y; swap_places(x, y);}
			else if(t == 1) {cin >> y; upd(x, y);}
			else if(t == 2) {cin >> y; add(x, y);}
			else if(t == 3) rem(x);
			else {cin >> y; cout << info[query(x, y)] << '\n';}
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