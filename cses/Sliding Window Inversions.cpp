#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, k;
	long long window {};
	ordered_set<pair<int, int>> st;
 
	cin >> n >> k;
 
	vector<int> a(n);
 
	for(int& v : a) cin >> v;
 
	auto count_greater = [&st](int x) {
		return (int)st.size() - (int)st.order_of_key(make_pair(x, INT_MAX));
	};
 
	auto count_lesser = [&st](int x) {
		return (int)st.order_of_key(make_pair(x, INT_MIN));
	};
 
	for(int i = 0; i < n; ++i) {
 
		if(i >= k) {
			window -= count_lesser(a[i - k]);
			st.erase(make_pair(a[i - k], i - k));
		}
 
		window += count_greater(a[i]);
 
		st.insert(make_pair(a[i], i));
 
		if(i >= k - 1) cout << window << ' ';
	}
 
	cout << '\n';
 
	return 0;
}
