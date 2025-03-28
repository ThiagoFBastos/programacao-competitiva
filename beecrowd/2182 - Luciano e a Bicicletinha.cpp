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
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;
const int maxn = 1e4;
int n, m, cc[maxn], maxd[maxn], sz, b;
vii G[maxn];
void dfs(int v) {
	cc[v] = 0;
	maxd[v] = v;
	sz += (int)G[v].size();
	for(auto [u, _] : G[v]) {
		if(cc[u] == -1) {
			b += _;
			dfs(u);
			maxd[v] = max(maxd[v], maxd[u]);
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int k = 0; k < m; ++k) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		G[a].push_back({b, c});
		G[b].push_back({a, c});
	}
	memset(cc, -1, sizeof(int) * n);
	int p = -1, q = -1, v = -1;
	for(int k = 0; k < n; ++k) {
		if(cc[k] == -1) {
			sz = b = 0;
			dfs(k);
			sz /= 2;
			if(sz == 0) sz = 1;
			if(p == -1) p = b, q = sz, v = maxd[k];
			else if(1LL * b * q < 1LL * p * sz) p = b, q = sz, v = maxd[k];
			else if(1LL * b * q == 1LL * p * sz) v = max(v, maxd[k]);
		}
	}
	cout << v + 1 << '\n';
	return 0;
}