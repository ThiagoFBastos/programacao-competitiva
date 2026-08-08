#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,mmx,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

bitset<100> st[1 << 20];
vvi T;
int N, Q, t = 1, sz;
vi C, lo, hi;

void dfs(int, int);
void upd(int, int);
void build();
bitset<100> query(int, int);

void dfs(int v, int p) {
	lo[v] = hi[v] = t++;
	for(int u : T[v]) {
		if(u == p) continue;
		dfs(u, v);
		hi[v] = max(hi[v], hi[u]);
	}
}

void upd(int k, int x) {
	int j = k;
	k = lo[k] + sz;
	st[k][C[j]] = 0;
	st[k][x] = 1;
	for(k >>= 1; k; k >>= 1) st[k] = st[k << 1] ^ st[(k << 1) ^ 1];
	C[j] = x;
}

void build() {
	sz = 1 << (32 - __builtin_clz(N + 1)); 
	for(int k = 0; k < N; ++k) st[sz + lo[k]][C[k]] = 1;
	for(int k = sz - 1; k > 0; --k) st[k] = st[k << 1] ^ st[(k << 1) | 1];
}

bitset<100> query(int l, int r) {
	bitset<100> ans;
	l += sz;
	r += sz;	
	while(l <= r) {
		if(l & 1) ans ^= st[l++];
		if(!(r & 1)) ans ^= st[r--];
		l >>= 1;
		r >>= 1;
	}
	return ans;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	T.resize(N);
	C.resize(N);
	lo.resize(N);
	hi.resize(N);
	for(int i = 0; i < N; ++i) {
		cin >> C[i];
		--C[i];
	}
	for(int i = 1; i < N; ++i) {
		int p;
		cin >> p;
		T[p - 1].push_back(i);
	}
	dfs(0, 0);
	build();
	while(Q--) {
		int K, X;
		cin >> K >> X;
		--X;
		if(K)
			upd(X, K - 1);	
		else {
			bitset<100> R = query(0, hi[X]);
			bitset<100> L = query(0, lo[X] - 1);
			cout << (R ^ L).count() << '\n';
		}
	}
	return 0;
}