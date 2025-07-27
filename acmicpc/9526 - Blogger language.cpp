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

const int N = 1e5 + 10;

int n, m, q, st[4*N][2], flips[4*N], is_sub[N];
string text, target;

int mis(string s) {
	int ans = 0;
	for(int i = 0; i < (int)s.size(); ++i) ans += s[i] != target[i];
	return ans;
}

void combine(int p) {
	for(int k : {0, 1}) st[p][k] = max(st[2*p][k],st[2*p+1][k]);
}

void build(int l, int r, int p = 1) {
	if(l == r) {
		st[p][0] = mis(text.substr(l, m));
		st[p][1] = m - st[p][0];
		if(!is_sub[l]) st[p][0] = st[p][1] = -INF;
	} else {
		int m = (l + r) / 2;
		build(l, m, 2 * p);
		build(m + 1, r, 2 * p + 1);
		combine(p);
	}
}

void push(int p) {
	for(int i : {2*p,2*p+1}) {	
		if(flips[p]) swap(st[i][0], st[i][1]);
		flips[i] ^= flips[p];
	}
	flips[p] = 0;
}

void upd(int l, int r, int lo, int hi, int p = 1) {
	if(l > r || lo > hi || r < lo || l > hi) return;
	else if(lo >= l && hi <= r) {
		flips[p] ^= 1;
		swap(st[p][0],st[p][1]);
		return;
	}
	int m = (lo+hi)/2;
	push(p);
	upd(l,r,lo,m,2*p);
	upd(l,r,m+1,hi,2*p+1);
	combine(p);	
}

char queryChar(int k, int l, int r, int p = 1) {
	if(l == r) return flips[p] ? (islower(text[k]) ? toupper(text[k]) : tolower(text[k])) : text[k];
	int m = (l + r) / 2;
	push(p);
	return k <= m ? queryChar(k, l, m, 2 * p) : queryChar(k, m + 1, r, 2 * p + 1);
}

int query(int l, int r, int lo, int hi, int p = 1) {
	if(l > r || lo > hi || r < lo || l > hi) return -INF;
	else if(lo >= l && hi <= r) return st[p][0];
	push(p);	
	int m = (lo+hi)/2;
	int a = query(l,r,lo,m,2*p), b = query(l,r,m+1,hi,2*p+1);
	return max(a,b);
}

void fixIT(int k, int l, int r, int p = 1) {
	if(l == r) {
		string t;
		for(int i = 0; i < m && i + k < n; ++i) t += queryChar(i + k, 0, n - 1);
		st[p][0] = mis(t);
		st[p][1] = m - st[p][0];
		if(!is_sub[k]) st[p][0] = st[p][1] = -INF;
		return;
	}
	int m = (l + r) / 2;
	push(p);
	if(k <= m) fixIT(k, l, m, 2 * p);
	else fixIT(k, m + 1, r, 2 * p + 1);
	combine(p);
}

bool same(string a, string b) {
	if(a.size()!=b.size()) return false;
	for(int i=0;i<(int)a.size();++i) {
		a[i]=tolower(a[i]);
		b[i]=tolower(b[i]);
		if(a[i]!=b[i])return false;
	}
	return true;
}

void solve() {
	cin >> q >> target >> text;

	n = text.size();
	m = target.size();

	for(int i = 0; i <= n - m; ++i) is_sub[i] = same(text.substr(i, m), target);
	
	build(0, n - 1);
	
	while(q--) {
		int l, r;
		cin >> l >> r;
		--l, --r;
		cout << max(-1, query(l, r - m + 1, 0, n - 1)) << '\n';
		upd(l, r, 0, n - 1);

		for(int i = max(0, r - m + 1); i <= r; ++i) fixIT(i, 0, n - 1);
		for(int i = max(0, l - m + 1); i < l; ++i) fixIT(i, 0, n - 1);
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