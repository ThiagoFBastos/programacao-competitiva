#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
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

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int c, p;
	while(cin >> c >> p) {
		vvi G(c);
		vector<bitset<1000>> S(c);
		int cnt = c * (c - 1) / 2;
		while(p--) {
			int u, v;
			cin >> u >> v;
			G[u - 1].push_back(v - 1);
		}
		for(int v = 0; v < c; ++v) 
			for(int u = 0; u < c; ++u)
				S[v][u] = 1;
		for(int v = 1; v < c; ++v) 
			S[0][v] = 0;
		for(int v = 0; v < c; ++v) {
			S[v][v] = 1;
			for(int u : G[v])
				S[u] &= S[v];
		}
		for(int v = 0; v < c; ++v)
			for(int u = v + 1; u < c; ++u)
				if((S[v] & S[u]).count() > 1) --cnt;
		cout << cnt << '\n';
	}
 	return 0;
}