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
	const double INF = 1e9;
	double desconto[15][15], dp[1 << 15], p[15];
	int n, preco[15], area[15];
	cout.precision(4);
	cout.setf(ios_base :: fixed);
	while(true) {
		cin >> n;
		if(n == 0) break;
		for(int i = 0; i < n; ++i) {
			int q;
			for(int k = 0; k < n; ++k)
				desconto[i][k] = 1;
			cin >> preco[i] >> area[i] >> q;
			for(int k = 0; k < q; ++k) {
				int x, d;		
				cin >> x >> d;
				desconto[i][x - 1] = (100 - d) / 100.0;
			}
		}
		int K = 1 << n;
		double r_m = INF;
		for(int i = 0; i < K; ++i) dp[i] = INF;
		for(int i = 0; i < n; ++i) dp[1 << i] = preco[i];
		for(int i = 1; i < K; ++i) {
			int a = 0;
			for(int k = 0; k < n; ++k) {
				if(1 << k & i) {
					a += area[k];
					p[k] = 1;
					for(int j = 0; j < n; ++j)
						if(1 << j & i) p[k] *= desconto[j][k];
				}
			}
			for(int k = 0; k < n; ++k) dp[i] = min(dp[i], dp[i ^ 1 << k] + preco[k] * p[k]);
			r_m = min(r_m, dp[i] / a);
		}
		cout << r_m << '\n';
	}
 	return 0;
}