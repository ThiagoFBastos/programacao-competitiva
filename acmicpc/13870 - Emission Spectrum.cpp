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

const int MAXS = 6e6 + 10;

#define NEUTRAL 0

struct comp {
	int operator()(int a, int b) {
		return a + b;
	}
};

int ls[MAXS], rs[MAXS], vroot[MAXS], st[MAXS];

struct PersistentSegTree {
	int size, nds, nv;

	int newnode() {
		ls[nds] = rs[nds] = -1;
		st[nds++] = NEUTRAL;
		return nds - 1;
	}

	void build(int p, int l, int r, int* A) {
		if(l == r) {
			st[p] = A ? A[l] : NEUTRAL;
			return;
		}

		ls[p] = newnode();
		rs[p] = newnode();

		int m = (l + r) / 2;

		build(ls[p], l, m, A);
		build(rs[p], m + 1, r, A);

		st[p] = comp()(st[ls[p]], st[rs[p]]);
	}

	void upd(int prv, int p, int l, int r, int i, int x) {
		if(i > r || i < l || l > r) return;

		if(l == r) {
			st[p] = st[prv] + x; // mudar se não for incremento
			return;
		}

		int m = (l + r) / 2;
		
		ls[p] = ls[prv], rs[p] = rs[prv];
		
		if(i <= m) {
			ls[p] = newnode();
			upd(ls[prv], ls[p], l, m, i, x);
		} else {
			rs[p] = newnode();
			upd(rs[prv], rs[p], m + 1, r, i, x);
		}
		
		st[p] = comp()(st[ls[p]], st[rs[p]]);
	}

	int query(int p, int l, int r, int a, int b) {
		if(a > r || b < l || l > r) return NEUTRAL;
		if(l >= a && r <= b) return st[p];
		int p1 = query(ls[p], l, (l + r) / 2, a, b);
		int p2 = query(rs[p], (l + r) / 2 + 1, r, a, b);
		return comp()(p1, p2);
	}

	int kth(int pl, int pr, int l, int r, int k) {
		if(l == r) return l;
		int m = (l + r) / 2, s_le = st[ls[pr]] - st[ls[pl]];
		if(k <= s_le) return kth(ls[pl], ls[pr], l, m, k);
		return kth(rs[pl], rs[pr], m + 1, r, k - s_le);
	}

	PersistentSegTree() {size = nds = nv = 0;}

	PersistentSegTree(int* be, int* en) {
		nds = nv = 0;
		size = int(en - be);
		vroot[nv++] = newnode();
		build(vroot[0], 0, size - 1, be);
	}

	PersistentSegTree(int _size) {
		nds = nv = 0;
		size = _size;
		vroot[nv++] = newnode();
		build(vroot[0], 0, size - 1, nullptr);
	}

	int query(int r, int lo, int hi) {
		return query(vroot[r], 0, size - 1, lo, hi);
	}

	int upd(int r, int i, int x) {
		vroot[nv++] = newnode();
		upd(vroot[r], vroot[nv - 1], 0, size - 1, i, x);
		return nv - 1;
	}
	
	int nver() {
		return nv - 1;
	}

	int kth(int l, int r, int k) {
		return kth(vroot[l - 1], vroot[r], 0, size - 1, k);
	}
};

void solve() {
	int n, q;

	cin >> n >> q;

	vector<int> I(n);

	for(int& v : I) cin >> v;
	
	auto coords = I;

	sort(all(coords));

	for(int& v : I) v = lower_bound(all(coords), v) - coords.begin();

	PersistentSegTree pst(n);

	for(int i = 1; i <= n; ++i) pst.upd(pst.nver(), I[i - 1], 1);

	while(q--) {
		char type;
		cin >> type;		
		if(type == 'Q') {
			int l, r, k;
			cin >> l >> r >> k;
			cout << coords[pst.kth(l, r, k)] << '\n';
		} else {
			int i;
			cin >> i;
			pst.upd(i, I[i - 1], -1);
			pst.upd(pst.nver(), I[i], 1);
			swap(vroot[i], vroot[pst.nver()]);
			swap(I[i], I[i - 1]);
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