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
	ordered_set<int> S;
	ll ans = 0;
	cin >> n;
	vi a(n + 1), b(n + 1);
	for(int k = 1; k <= n; ++k) cin >> a[k];
	for(int k = 1; k <= n; ++k) {
		int x;
		cin >> x;
		b[x] = k;
	}
	for(int k = 1; k <= n; ++k) a[k] = b[a[k]];
	for(int k = 1; k <= n; ++k) {
		ans += (int)S.size() - S.order_of_key(a[k]);
		S.insert(a[k]);
	}
	cout << (ans & 1 ? "Impossible\n" : "Possible\n");
	return 0;
}