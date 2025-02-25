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
 
const int N = 3e5 + 100;

int lc[N], rc[N], nd = 1;
i64 key[N], prior[N], sum[N], value[N];

int newnode(i64 _key, i64 _prior, i64 _value) {
	key[nd] = _key;
	prior[nd] = _prior;
	value[nd] = _value;
	sum[nd] = 0;
	lc[nd] = rc[nd] = 0;
	return nd++;
}

void refresh(int T) {
	sum[T] = value[T] + sum[lc[T]] + sum[rc[T]];
}

void split(int T, i64 skey, int& l, int& r) {
	if(!T) {l = r = 0; return;}
	if(key[T] <= skey) {
		split(rc[T], skey, rc[T], r);
		l = T;
	} else {
		split(lc[T], skey, l, lc[T]);
		r = T;
	}
	refresh(T);
}

int merge(int T1, int T2) {
	if(!T1 && T2) {refresh(T2); return T2;}
	if(T1 && !T2) {refresh(T1); return T1;}
	if(prior[T1] < prior[T2]) {
		lc[T2] = merge(T1, lc[T2]);
		refresh(T2);
		return T2;
	}
	rc[T1] = merge(rc[T1], T2);
	refresh(T1);
	return T1;
}

i64 query(int T, i64 k) {
	if(!T) return 0;
	else if(key[T] > k) return query(lc[T], k);
	return query(rc[T], k) + sum[T] - sum[rc[T]];
}

int root {};

const i64 MAXN = 1ll << 60;
uniform_int_distribution<i64> uid(0, MAXN);

void add(i64 x, i64 y) {
	int p = newnode(x, uid(rng), y), a, b;
	split(root, x, a, b);
	root = merge(merge(a, p), b);
}

void solve() {
	int q; 
	i64 l = 0;
	cin >> q;
	while(q--) {
		i64 a, v;
		cin >> a >> v;
		a ^=  l, v ^= l;
		add(a, v);
		l = query(root, a);	
		cout << a << ' ' << l << '\n';
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
