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
 
const int N = 2e5 + 100;
const i64 MAXN = 1ll << 60;

uniform_int_distribution<i64> uid(0, MAXN);
int l[N], r[N], sub[N], nd = 1, root, key[N];
i64 pry[N];

int newnode(int _key, i64 _pry) {
	key[nd] = _key;
	pry[nd] = _pry;
	sub[nd] = 1;
	l[nd] = r[nd] = 0;
	return nd++;
}

void refresh(int p) {
	sub[p] = 1 + sub[l[p]] + sub[r[p]];
}

void split(int t, int k, int& L, int& R) {
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
	if(pry[t1] < pry[t2]) {
		l[t2] = merge(t1, l[t2]);
		refresh(t2);
		return t2;
	}
	r[t1] = merge(r[t1], t2);
	refresh(t1);
	return t1;
}

int order_of_key(int t, int k) {
	if(!t) return 0;
	else if(key[t] > k) return order_of_key(l[t], k);
	return sub[t] - sub[r[t]] + order_of_key(r[t], k);
}

int order_of_key(int k) {
	return order_of_key(root, k);
}

int find_by_order(int t, int n) {
	int m = sub[t] - sub[r[t]];
	if(n == m) return key[t];
	else if(n > m) return find_by_order(r[t], n - m);
	return find_by_order(l[t], n);
}

int find_by_order(int n) {
	if(nd <= n) return -1;
	return find_by_order(root, n);
}

void add(int k) {
	int p = newnode(k, uid(rng)), a, b;
	split(root, k, a, b);
	root = merge(merge(a, p), b);
}

void heapfy(int t) {
	if(!t) return;
	int u = t;
	if(l[t] && pry[l[t]] > pry[u]) u = l[t];
	if(r[t] && pry[r[t]] > pry[u]) u = r[t];
	if(u != t) {
		swap(pry[t], pry[u]);
		heapfy(u);
	}
}

int build(int keys[], int lo, int hi) {
	if(lo > hi) return 0;
	int m = (lo + hi) / 2, p = newnode(keys[m], uid(rng));
	l[p] = build(keys, lo, m - 1);
	r[p] = build(keys, m + 1, hi);
	refresh(p);
	heapfy(p);
	return p;
}

int n, q, a[N];

void solve() {

	cin >> n >> q;

	for(int i = 0; i < n; ++i) cin >> a[i];

	sort(a, a + n);

	root = build(a, 0, n - 1);

	while(q--) {
		int t, x;
		cin >> t >> x;
		if(t == 1) add(x + order_of_key(x));
		else if(t == 2) cout << order_of_key(x) << '\n';
		else {
			int ans = find_by_order(x);
			if(ans < 0) cout << "invalid\n";
			else cout << ans << '\n';
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
