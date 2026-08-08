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

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;	
	cin >> n;
	vector<string> g(n);
	vi p(n, 0);
	vvi pq(n + 1);
	for(int k = 0; k < n; ++k) cin >> g[k];
	bool ok = true;
	for(int i = 1; i <= n; ++i) {
		int opn = 0, cls = 0;
		for(int k = 0; k < n; ++k) {
			if(g[k][i - 1] == '(') ++opn;
			else ++cls;
			pq[p[k]].push_back(k);
		}
		for(int k = i; k >= 0; --k) {
			for(int j : pq[k]) {
				if(cls) {
					--cls;
					if(k == 0) {
						ok = false;
						goto fim;
					}
					--p[j];
				} else {
					--opn;
					++p[j];
				}
			}
			pq[k].clear();
		}
	}
	for(int k = 0; k < n; ++k) {
		if(p[k]) {
			ok = false;
			break;
		}	
	}
	fim: cout << (ok ? "Yes\n" : "No\n");
	return 0;
}