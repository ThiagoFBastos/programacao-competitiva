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
	int t = 1, inv[1000][2];
	while(true) {
		int n, r, q;
		cin >> n >> r;
		if(!n) break;
		for(int i = 0; i < r; ++i)
			for(int k = 0; k < 2; ++k)
				cin >> inv[i][k];
		cin >> q;
		cout << "Genome " << t++ << '\n';
		while(q--) {
			int pos;
			cin >> pos;
			for(int i = 0; i < r; ++i) {
				if(pos < inv[i][0] || pos > inv[i][1]) continue;
				pos = inv[i][0] + inv[i][1] - pos;
			}
			cout << pos << '\n';
		}
	}
	return 0;
}