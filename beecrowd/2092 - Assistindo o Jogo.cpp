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
	int n, f, a, b, c, q;
	set<ii> X;

	cin >> n >> f >> a >> b >> c >> q;

	vector<int> e(n + 1);

	e[1] = a;

	X.insert({a, 1});

	for(int k = 2; k <= n; ++k) {
		e[k] = (1LL * b * e[k - 1] + c) % f; 
		X.insert({e[k], k});
	}

	while(q--) {

		int x, y;

		cin >> x >> y;

		if(e[x] != y) {
			X.erase({e[x], x});
			X.insert({y, x});	
			e[x] = y;
		}

		auto F = X.lower_bound({y, x});
		auto S = X.upper_bound({y, x});

		if(F == X.begin() || prev(F)->first != y)
			F = prev(X.lower_bound({y + 1, -1}));

		else
			F = prev(F);
		
		if(S == X.end() || S->first != y)
			S = X.lower_bound({y, -1});

		if(F->second < x) cout << x - F->second << ' ';
		else cout << n - F->second + x << ' ';

		if(x < S->second) cout << S->second - x << '\n';
		else cout << n - x + S->second << '\n';
	}
	return 0;
}