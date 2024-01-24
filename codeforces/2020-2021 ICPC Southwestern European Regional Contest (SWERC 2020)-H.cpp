#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
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

struct node {
	int sum;
	node *l, *r;
	node() {
		sum = 0;
		l = r = nullptr;
	}
};

const int N = 1e5 + 10;

node *root[N];

node *build(int l, int r) {
	node *p = new node;
	if(l != r) {
		int m = (l + r) / 2;
		p->l = build(l, m);
		p->r = build(m + 1, r);
	}
	return p;
}

node *upd(int k, int x, int lo, int hi, node* v) {
	node *p = new node;
	*p = *v;
	p->sum += x;
	if(lo != hi) {
		int m = (lo + hi) / 2;
		if(k <= m) p->l = upd(k, x, lo, m, v->l);
		else p->r = upd(k, x, m + 1, hi, v->r);
	}
	return p;
}

int query(int l, int r, int lo, int hi, node* p) {
	if(l > r || r < lo || l > hi) return 0;
	else if(lo >= l && hi <= r) return p->sum;
	int m = (lo + hi) / 2;
	int e = query(l, r, lo, m, p->l);
	int d = query(l, r, m + 1, hi, p->r);
	return e + d; 
}

void solve() {
	int n;
	cin >> n;
	root[0] = build(0, n);
	cin.ignore();
	for(int i = 1; i <= n; ++i) {
		string s;
		getline(cin, s);
		istringstream is(s);
		root[i] = root[i - 1];
		while(is >> s) {
			string p = s.substr(1);
			int x = stoi(p);
			if(s[0] == '+') root[i] = upd(x, 1, 0, n, root[i]);
			else root[i] = upd(x, -1, 0, n, root[i]);
		}
	}
	int x = 0;
	for(int i = 1; i <= n; ++i) {
		int d;
		cin >> d;
		int cnt = query(x, n, 0, n, root[d]);
		x = (x + cnt) % n;
	}
	cout << x << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
