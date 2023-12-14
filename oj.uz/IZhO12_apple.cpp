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
 
struct No {
	int cnt;
	bool lazy;
	No *left, *right;
	No() {
		cnt = 0;
		lazy = false;
		left = right = nullptr;
	}
} *r {};
 
void push(No **p, int n) {
	if(!*p || !(*p)->lazy) return;
	if(!(*p)->left) (*p)->left = new No;
	if(!(*p)->right) (*p)->right = new No;
	No* left = (*p)->left, *right = (*p)->right;
	left->lazy = right->lazy = true;
	left->cnt = (n + 1) / 2;
	right->cnt = n / 2;
	(*p)->lazy = false;
}
 
void upd(int l, int r, int lo, int hi, No **p) {
	if(l > r || lo > hi || r < lo || l > hi) return;
	else if(lo >= l && hi <= r) {
		if(!*p) *p = new No;
		(*p)->lazy = true;
		(*p)->cnt = hi - lo + 1;
		return;
	}
	int m = (lo + hi) / 2;
	push(p, hi - lo + 1);
	if(!*p) *p = new No;
	upd(l, r, lo, m, &(*p)->left);
	upd(l, r, m + 1, hi, &(*p)->right);
	No *left = (*p)->left, *right = (*p)->right;
	if(left && right) (*p)->cnt = left->cnt + right->cnt;
	else (*p)->cnt = left ? left->cnt : right->cnt;
}
 
int query(int l, int r, int lo, int hi, No **p) {
	if(l > r || lo > hi || r < lo || l > hi || !*p) return 0;
	else if(lo >= l && hi <= r) return (*p)->cnt;
	int m = (lo + hi) / 2;
	push(p, hi - lo + 1);
	int v1 = query(l, r, lo, m, &(*p)->left);
	int v2 = query(l, r, m + 1, hi, &(*p)->right);
	return v1 + v2;
}
 
void solve() {
	int c = 0, q;
 
	cin >> q;
 
	while(q--) {
		int t, x, y;
		cin >> t >> x >> y;
		x += c, y += c;
		if(t == 1) {
			int ans = query(x, y, 1, INF, &r);
			cout << ans << '\n';
			c = ans;
		} else upd(x, y, 1, INF, &r);
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
