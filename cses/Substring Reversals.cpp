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
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<i64> uid(0ll, 1ll<<62);
 
struct node {
	int key;
	i64 pry;
	int prop;
	char value;
	node *l, *r;
};
 
node* null() {
	static node nul {};
	return &nul;
}
 
node *root {null()};
 
node* newnode(char value) {
	auto t = new node;
	t->key = 1;
	t->value = value;	
	t->pry = uid(rng);
	t->prop = 0;
	t->l = t->r = nullptr;
	return t;
}
 
void flip(node* t) {
	if(t == null()) return;
	t->prop ^= 1;
	swap(t->l, t->r);
}
 
void refresh(node* t) {
	if(t == null()) return;
	if(t->prop) {
		flip(t->l);
		flip(t->r);
		t->prop = 0;
	}
	t->key = 1 + t->l->key + t->r->key;
}
 
void split(node* t, int k, node*& L, node*& R) {
	refresh(t);
	if(t == null()) {L = R = null(); return;}
	if(t->l->key + 1 <= k) {
		split(t->r, k - t->l->key - 1, t->r, R);
		L = t;
	} else {
		split(t->l, k, L, t->l);
		R = t;
	}
	refresh(t);
}
 
node* merge(node* t1, node* t2) {	
	refresh(t1);
	refresh(t2);
	if(t1 == null() || t2 == null()) return t2 != null() ? t2 : t1;
	if(t1->pry < t2->pry) {
		t2->l = merge(t1, t2->l);
		refresh(t2);
		return t2;
	}
	t1->r = merge(t1->r, t2);
	refresh(t1);
	return t1;
}
 
void heapfy(node* t) {
	if(t == null()) return;
	node* u = t;
	if(t->l != null() && t->l->pry > u->pry) u = t->l;
	if(t->r != null() && t->r->pry > u->pry) u = t->r;
	if(u != t) {
		swap(t->pry, u->pry);
		heapfy(u);
	}
}
 
node* build(string& s, int lo, int hi) {
	if(lo > hi) return null();
	int m = (lo + hi) / 2;
	node* p = newnode(s[m]);
	p->l = build(s, lo, m - 1);
	p->r = build(s, m + 1, hi);
	refresh(p);
	heapfy(p);
	return p;
}
 
void build(string& s) {
	root = build(s, 0, (int)s.size() - 1);
}
 
void reverse(int l, int r) {
	node *p1, *p2, *p3;
	split(root, l - 1, p1, p2);
	split(p2, r - l + 1, p2, p3);
	flip(p2);
	root = merge(p1, merge(p2, p3));
}
 
void dfs(node* t) {
	if(t == null()) return;
	refresh(t);
	dfs(t->l);
	cout << t->value;
	dfs(t->r);
}
 
void solve() {
	int n, q;
	string s;
	cin >> n >> q >> s;
	build(s);
	while(q--) {
		int l, r;
		cin >> l >> r;
		reverse(l, r);
	}
	dfs(root);
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
