#pragma GCC optimize("O3")

#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

const int N = 1e5 + 1;
int F[N], G[N], mobius[N];
vector<int> P[N];
ordered_set<int> pos[N];

void solve() {
	int n, q;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		a[i] = G[a[i]];
		for(int x : P[a[i]]) pos[x].insert(i);
	}
	cin >> q;
	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int x, y;
			cin >> x >> y;
			--x;
			for(int v : P[a[x]]) pos[v].erase(x);
			a[x] = G[y];
			for(int v : P[a[x]]) pos[v].insert(x);
		} else {
			int l, r, g, cnt = 0;
			cin >> l >> r >> g;
			--l, --r;
			g = G[g];
			for(int x : P[g]) cnt += mobius[x] * int(pos[x].order_of_key(r + 1) - pos[x].order_of_key(l));
			cout << r - l + 1 - cnt << '\n';
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	for(int k = 2; k * k < N; ++k) {
		if(F[k]) continue;
		for(int i = k; i < N; i += k) F[i] = k;
	}
	mobius[1] = -1;
	G[1] = 1;
	for(int k = 2; k < N; ++k) {
		if(!F[k]) F[k] = k;
		int f = F[k];
		if(f == F[k / f]) mobius[k] = 0;
		else {
			P[k] = P[k / f];
			mobius[k] = -mobius[k / f];
			for(int x : P[k / f]) P[k].push_back(x * f);
			P[k].push_back(f);
		}
		if(G[k / f] % f == 0) G[k] = G[k / f];
		else G[k] = G[k / f] * f;
	}
	solve();
	return 0;
}
