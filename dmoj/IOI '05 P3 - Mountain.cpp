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

struct Node {
	int lz;
	bool mk;
	i64 pre;
	i64 sum;
	Node *left, *right;
	Node() {
		mk = false;
		lz = pre = sum = 0;
		left = right = nullptr;
	}
};

Node *root;
int n;

void push(Node* k, int n) {
	if(!k->left) k->left = new Node;
	if(!k->right) k->right = new Node;
	if(!k->mk) return;

	Node *l = k->left, *r = k->right;

	l->lz = k->lz;
	l->mk = true;
	l->sum = (n + 1ll) / 2 * k->lz;
	l->pre = max(0ll, l->sum);

	r->lz = k->lz;		
	r->mk = true;
	r->sum = n / 2ll * k->lz;
	r->pre = max(0ll, r->sum);

	k->mk = false;
}

void upd(int l, int r, int x, int lo, int hi, Node *p) {
	if(l > r || lo > hi || r < lo || l > hi) return;
	else if(lo >= l && hi <= r) {
		p->lz = x;
		p->mk = true;
		p->sum = (hi - lo + 1ll) * x;
		p->pre = max(0ll, p->sum);
		return;
	}

	int m = (lo + hi) / 2;

	push(p, hi - lo + 1);

	upd(l, r, x, lo, m, p->left);
	upd(l, r, x, m + 1, hi, p->right);

	p->sum = p->left->sum + p->right->sum;
	p->pre = max(p->left->pre, p->left->sum + p->right->pre);
}

int query(int h, int lo, int hi, Node* p, i64 s = 0) {
	if(!p || s + p->pre <= h) return n + 1;
	if(lo == hi) return lo;
	push(p, hi - lo + 1);
	int m = (lo + hi) / 2;
	int ans = query(h, lo, m, p->left, s); 
	return ans != n + 1 ? ans : query(h, m + 1, hi, p->right, s + p->left->sum);
}

void solve() {

	cin >> n;

	root = new Node;

	while(true) {
		char t;
		cin >> t;
		if(t == 'I') {
			int a, b, d;
			cin >> a >> b >> d;
			upd(a, b, d, 0, n, root);
		} else if(t == 'Q') {
			int h;
			cin >> h;
			cout << query(h, 0, n, root) - 1 << '\n';
		} else
			break;
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
