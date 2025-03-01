#include "bits/stdc++.h"
using namespace std;
vector<int> p, q;
int n;
struct Node {
	Node *left, *right;
	int cnt;
};
struct SegTree {
	vector<Node*> rt;
	Node *build(int lo, int hi) {
		auto no = new Node;
		no->cnt = 0;
		no->left = no->right = nullptr;
		if(lo != hi) {
			int mid = (lo + hi) / 2;
			no->left = build(lo, mid);
			no->right = build(mid + 1, hi);
		}
		return no;
	}
	Node *upd(int k, int lo, int hi, Node *r) {
		auto no = new Node;
		if(lo == hi) {
			no->cnt = r->cnt + 1;
			no->left = no->right = nullptr;
		} else {
			int mid = (lo + hi) / 2;
			if(k <= mid) {
				no->left = upd(k, lo, mid, r->left);
				no->right = r->right;
			} else {
				no->left = r->left;
				no->right = upd(k, mid + 1, hi, r->right);
			}
			no->cnt = no->left->cnt + no->right->cnt;
		}
		return no;
	}
	int k_th(int k, int lo, int hi, Node *L, Node *R) {
		if(lo == hi) return q[lo];
		int mid = (lo + hi) >> 1;
		int cnt = R->left->cnt - L->left->cnt;
		if(cnt >= k) return k_th(k, lo, mid, L->left, R->left);
		return k_th(k - cnt, mid + 1, hi, L->right, R->right);
	}
	SegTree() {
		rt.resize(n + 1);
		rt[0] = build(0, n - 1);
		for(int i = 1; i <= n; ++i) rt[i] = upd(p[i - 1], 0, n - 1, rt[i - 1]);
	}
	int k_th(int l, int r, int k) {
		return k_th(k, 0, n - 1, rt[l - 1], rt[r]);
	}
	long long solve(int L, int R) {
		if(L >= R) return 0;
		int k = k_th(L, R, (R - L + 2) / 2);
		return R - L + 1 + solve(L, k - 1) + solve(k + 1, R);
	}
};
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	q.resize(n);
	p.resize(n);
	for(int i = 0; i < n; ++i) {
		cin >> q[i];
		p[q[i] - 1] = i;
	}
	SegTree st;
	cout << st.solve(1, n) << '\n';
	return 0;
}