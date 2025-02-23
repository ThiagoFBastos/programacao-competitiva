#include "bits/stdc++.h"

using namespace std;

const int inf = 1e9;
int n, q;
vector<int> a, p, c;

void dfs(int v) {
	int u = a[v];
	p[v] = v;
	if(p[u] == inf) dfs(u);
	else c[v] = u;
	if(c[u] != -1) c[v] = c[u];
	p[v] = min(p[v], p[u]);
	if(c[v] == v) c[v] = -1;
}

struct node {
	int cnt;
	node *l, *r;
};

struct segtree {
	vector<node*> root;
	pair<int, int> ans1, ans2;
	int len;
	node *build(int lo, int hi) {
		node *no = new node;
		no->cnt = 0;
		no->l = no->r = nullptr;
		if(lo != hi) {
			int mid = (lo + hi) >> 1;
			no->l = build(lo, mid);
			no->r = build(mid + 1, hi);
		}
		return no;
	}
	node *upd(int k, int lo, int hi, node *rt) {
		node *no = new node;
		if(lo == hi) {
			no->cnt = rt->cnt + 1;
			no->l = no->r = nullptr;
		} else {
			int mid = (lo + hi) >> 1;
			if(k <= mid) {
				no->l = upd(k, lo, mid, rt->l);
				no->r = rt->r;
			} else {
				no->r = upd(k, mid + 1, hi, rt->r);
				no->l = rt->l;
			}
			no->cnt = no->l->cnt + no->r->cnt;
		}
		return no;
	}
	void query1(int inc, int lo, int hi, node* L, node* R) {
		if(lo == hi) ans1 = min(ans1, make_pair(abs(2 * (inc + R->cnt - L->cnt) - len), lo));
		else {
			int mid = (lo + hi) >> 1;
			node *LL = L->l, *LR = L->r, *RL = R->l, *RR = R->r;
			int cnt1 = inc + RL->cnt - LL->cnt;
			int cnt2 = len - cnt1;
			ans1 = min(ans1, make_pair(abs(cnt1 - cnt2), mid));
			if(cnt1 >= cnt2) query1(inc, lo, mid, LL, RL);
			else query1(cnt1, mid + 1, hi, LR, RR);
		}
	}
	void query2(int inc, int lo, int hi, node* L, node* R) {
		if(lo == hi) ans2 = min(ans2, make_pair(abs(2 * (inc + R->cnt - L->cnt) - len), lo));
		else {
			int mid = (lo + hi) >> 1;
			node *LL = L->l, *RL = R->l;
			int cnt1 = inc + RL->cnt - LL->cnt;
			int cnt2 = len - cnt1;
			ans2 = min(ans2, make_pair(abs(cnt1 - cnt2), mid));
			if(mid >= ans1.second || abs(cnt1 - cnt2) == ans1.first) query2(inc, lo, mid, LL, RL);
			else query2(cnt1, mid + 1, hi, L->r, R->r);
		}
	}
	int query(int l, int r) {
		ans1 = ans2 = {inf, inf};
		len = r - l + 1;
		query1(0, 0, n - 1, root[l - 1], root[r]);
		query2(0, 0, n - 1, root[l - 1], root[r]);
		return ans2.second + 1;
	}
	segtree() {
		root.resize(n + 1);
		root[0] = build(0, n - 1);
		for(int i = 1; i <= n; ++i) root[i] = upd(p[i - 1], 0, n - 1, root[i - 1]);
	}
};

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	a.resize(n);
	p.assign(n, inf);
	c.assign(n, -1);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		--a[i];
	}
	for(int i = 0; i < n; ++i) {
		if(p[i] == inf) dfs(i);
		if(c[i] != -1) p[i] = min(p[i], p[c[i]]);
	}
	segtree st;
	while(q--) {
		int l, r;
		cin >> l >> r;
		cout << st.query(l, r) << '\n';
	}
	return 0;
}