#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
using namespace std;
 
template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
 
void solve() {
	int n, k, x;
	cin >> n >> k;
	ordered_set<int> S;
	for(int i = 1; i <= n; ++i) S.insert(i);
	x = k % n + 1;
	while(S.size() > 1) {
		int kth = S.order_of_key(x);
		cout << x << ' ';
		if(kth == int(size(S)) - 1) kth = 0;
		S.erase(x);
		x = *S.find_by_order((kth + k) % int(size(S)));
	}
	cout << *S.begin() << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
