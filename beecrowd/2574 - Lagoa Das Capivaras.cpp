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
const int maxn = 2049;
int p[maxn][maxn];
int query(int x0, int y0, int x1, int y1) {
	return p[x1][y1] - p[x0 - 1][y1] - p[x1][y0 - 1] + p[x0 - 1][y0 - 1];
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, g, areas = 0;	
	cin >> n >> g;	
	for(int i = 0; i <= n; ++i) 
		p[0][i] = p[i][0] = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			cin >> p[i][j];
			p[i][j] += p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1]; 
		}
	}
	for(int k = 1; k <= n; k <<= 1) {
		int minG = INT_MAX;
		for(int i = 1; i <= 1 + n - k && minG >= g; i += k)
			for(int j = 1; j <= 1 + n - k && minG >= g; j += k)
				minG = min(minG, query(i, j, i + k - 1, j + k - 1));
		if(minG >= g) {
			areas = (n / k) * (n / k);
			break;
		}
	}
	cout << areas << '\n';
	return 0;
}