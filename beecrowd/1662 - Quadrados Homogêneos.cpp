#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true) {
		int n;
		cin >> n;
		if(n == 0) break;
		vector<vector<int>> a(n);
		for(int i = 0; i < n; ++i) {
			a[i].resize(n);
			for(int j = 0; j < n; ++j)
				cin >> a[i][j];
		}
		bool ok = true;
		for(int i = 0; i < n - 1; ++i) {
			for(int j = 0; j < n - 1; ++j) {
				if(a[i][j] + a[i + 1][j + 1] != a[i][j + 1] + a[i + 1][j]) {
					ok = false;
					goto fim;
				}
			}
		}	
		fim: cout << (ok ? "homogeneous\n" : "not homogeneous\n");
	}
	return 0;
}