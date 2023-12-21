#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag ,  tree_order_statistics_node_update >
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 2e5;
	int n, k, a[MAXN];
	ordered_set S;
	cin >> n >> k;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	for(int i = 0; i < k - 1; ++i)
		S.insert(a[i]);
	for(int i = k - 1; i < n; ++i) {
		S.insert(a[i]);
		cout << *S.find_by_order((k - 1) / 2) << ' ';
		S.erase(S.find_by_order(S.order_of_key(a[i - k + 1])));
	}
	cout << '\n';
	return 0;
}
