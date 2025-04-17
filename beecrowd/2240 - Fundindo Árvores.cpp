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
const int maxn = 1e4 + 1;
int n, m, esq[maxn][2], dir[maxn][2], cesq[maxn], cdir[maxn];
void dfs_1(int node) {
	if(esq[node][0]) 
		dfs_1(esq[node][0]);
	if(esq[node][1]) {
		dfs_1(esq[node][1]);
		cesq[node] = 1 + cesq[esq[node][1]];
	}
}
void dfs_2(int node) {
	if(dir[node][1])
		dfs_2(dir[node][1]);
	if(dir[node][0]) {
		dfs_2(dir[node][0]);
		cdir[node] = 1 + cdir[dir[node][0]];
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cesq[i] = 0;
	for(int i = 1; i <= n; ++i) {
		int no;
		cin >> no;
		for(int k = 0; k < 2; ++k)
			cin >> esq[no][k];
	}
	cin >> m;
	for(int i = 1; i <= m; ++i) cdir[i] = 0;
	for(int i = 1; i <= m; ++i) {
		int no;
		cin >> no;
		for(int k = 0; k < 2; ++k)
			cin >> dir[no][k];
	}
	dfs_1(1);
	dfs_2(1);
	int x = 0, y = 0;
	for(int i = 1; i <= n; ++i) x = max(x, cesq[i]);
	for(int i = 1; i <= m; ++i) y = max(y, cdir[i]);
	cout << n + m - 1 - max(min(x, cdir[1]), min(cesq[1], y)) << '\n';
	return 0;
}