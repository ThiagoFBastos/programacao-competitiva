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

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
 
const int N = 4e5 + 100;

int l[N], r[N], sub[N], nd = 1, root;
ii key[N];
i64 prior[N];

int newnode(ii _key, i64 _prior) {
	key[nd] = _key;
	prior[nd] = _prior;
	sub[nd] = 1;
	l[nd] = r[nd] = 0;
	return nd++;
}

void refresh(int p) {
	if(!p) return;
	sub[p] = 1 + sub[l[p]] + sub[r[p]];
}

void split(int t, ii k, int& L, int& R) {
	if(!t) {L = R = 0; return;}
	if(key[t] <= k) {
		split(r[t], k, r[t], R);
		L = t;
	} else {
		split(l[t], k, L, l[t]);
		R = t;
	}
	refresh(t);
}

int merge(int t1, int t2) {
	if(!t1 || !t2) return t2 ? t2 : t1;
	if(prior[t1] < prior[t2]) {
		l[t2] = merge(t1, l[t2]);
		refresh(t2);
		return t2;
	}
	r[t1] = merge(r[t1], t2);
	refresh(t1);
	return t1;
}

int erase(int t, ii k) {
	if(key[t] == k) return merge(l[t], r[t]);
	else if(k <= key[t]) l[t] = erase(l[t], k);
	else r[t] = erase(r[t], k);
	refresh(t);	
	return t;
}

void erase(ii k) {
	root = erase(root, k);
}

int order_of_key(int t, ii k) {
	if(!t) return 0;
	else if(key[t] > k) return order_of_key(l[t], k);
	return sub[t] - sub[r[t]] + order_of_key(r[t], k);
}

const i64 MAXN = 1ll << 60;
uniform_int_distribution<i64> uid(0, MAXN);

void add(ii k) {
	int p = newnode(k, uid(rng)), a, b;
	split(root, k, a, b);
	root = merge(merge(a, p), b);
}

int n, q, a[N];
ii b[N];

void heapfy(int t) {
	if(!t) return;
	int u = t;
	if(l[t] && prior[l[t]] > prior[u]) u = l[t];
	if(r[t] && prior[r[t]] > prior[u]) u = r[t];
	if(u != t) {
		swap(prior[t], prior[u]);
		heapfy(u);
	}
}

int build(int lo, int hi) {
	if(lo > hi) return 0;
	int m = (lo + hi) / 2, p = newnode(b[m], uid(rng));
	l[p] = build(lo, m - 1);
	r[p] = build(m + 1, hi);
	refresh(p);
	heapfy(p);
	return p;
}

void solve() {
	
	cin >> n >> q;

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		b[i] = {a[i], i};
	}

	sort(b, b + n);
	root = build(0, n - 1);

	while(q--) {
		int i, v;
		cin >> i >> v;	
		erase({a[i], i});
		add({v, i});
		a[i] = v;
		cout << order_of_key(root, {a[i], i - 1}) - order_of_key(root, {a[i], -1}) << '\n';
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
