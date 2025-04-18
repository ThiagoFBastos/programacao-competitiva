#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2,sse3")
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
	int v;
	int cnt[2];
	int rev;
	i64 pry;
	int l, r;
};

const int N = 1e5 + 10;
int a[N], nd, root;
node treap[N];

int newnode(int v) {
	auto& t = treap[nd];
	t.key = 1;
	t.v = v;
	t.cnt[v] = 1, t.cnt[v^1] = 0;
	t.pry = uid(rng);
	t.rev = 0;
	t.l = t.r = 0;
	return nd++;
}

void applyRev(int t) {
	if(!t) return;
	auto& u = treap[t];
	u.rev ^= 1;
	swap(u.l, u.r);
}

void refresh(int t) {
	if(!t) return;
	auto& u = treap[t];
	if(u.rev) {
		u.rev = 0;
		applyRev(u.l);
		applyRev(u.r);
	}
	u.key = 1 + treap[u.l].key + treap[u.r].key;
	for(int i = 0; i < 2; ++i) u.cnt[i] = treap[u.l].cnt[i] + treap[u.r].cnt[i];
	++u.cnt[u.v];
}

void split(int t, int k, int& L, int& R) {
	refresh(t);
	if(!t) {L = R = 0; return;}
	auto& u = treap[t];
	if(treap[u.l].key + 1 <= k) {
		split(u.r, k - treap[u.l].key - 1, u.r, R);
		L = t;
	} else {
		split(u.l, k, L, u.l);
		R = t;
	}
	refresh(t);
}

int merge(int t1, int t2) {
	refresh(t1);
	refresh(t2);
	if(!t1 || !t2) return t2 ? t2 : t1;
	node &T1 = treap[t1], &T2 = treap[t2];
	if(T1.pry < T2.pry) {
		T2.l = merge(t1, T2.l);
		refresh(t2);
		return t2;
	}
	T1.r = merge(T1.r, t2);
	refresh(t1);
	return t1;
}

void heapfy(int t) {
	if(!t) return;
	int u = t;
	auto& T = treap[t];
	if(T.l && treap[T.l].pry > treap[u].pry) u = T.l;
	if(T.r && treap[T.r].pry > treap[u].pry) u = T.r;
	if(u != t) {
		swap(T.pry, treap[u].pry);
		heapfy(u);
	}
}

int build(int a[], int lo, int hi) {
	if(lo > hi) return 0;
	int m = (lo + hi) / 2;
	int p = newnode(a[m]);
	treap[p].l = build(a, lo, m - 1);
	treap[p].r = build(a, m + 1, hi);
	refresh(p);
	heapfy(p);
	return p;
}

void build(int a[], int n) {
	memset(&treap[0], 0, sizeof treap[0]);
	nd = 1;
	root = build(a, 0, n - 1);
}

void reverse(int l, int r) {
	int a, b, c;
	split(root, l - 1, a, b);
	split(b, r - l + 1, b, c);
	applyRev(b);	
	root = merge(a, merge(b, c));
}

void upd(int k, int v) {
	int a, b, c;
	split(root, k - 1, a, b);
	split(b, 1, b, c);
	treap[b].v = v & 1;
	root = merge(a, merge(b, c));
}

ii query(int l, int r) {
	int a, b, c;
	split(root, l - 1, a, b);
	split(b, r - l + 1, b, c);
	ii ans = {treap[b].cnt[0], treap[b].cnt[1]};
	root = merge(a, merge(b, c));
	return ans;
}

void solve() {
	int p, q;
	while(cin >> p >> q) {
		for(int i = 0; i < p; ++i) {
			cin >> a[i];
			a[i] &= 1;
		}
		build(a, p);
		while(q--) {
			char t;
			int a, b;
			cin >> t >> a >> b;
			if(t == 'S') upd(a, b);
			else if(t == 'E') cout << query(a, b).fi << '\n';
			else if(t == 'O') cout << query(a, b).sc << '\n';
			else reverse(a, b);
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