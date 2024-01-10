#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;


template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

void solve() {
	int n, k;
	cin >> n >> k;
	
	map<int, ordered_set<ii>> cnt;
	
	i64 pre = 0, ans = 0;
	
	cnt[0].insert(make_pair(0, 0));
	
	for(int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		
		pre += x;
		pre %= k;
		
		auto it = cnt.find(pre - i);
		
		if(it != cnt.end()) {
			auto& S = it->second;
			auto k = S.lower_bound(make_pair(pre + 1, 0));
			if(k != S.end()) ans += S.order_of_key(*k);
			else ans += S.size();
		}
		
		it = cnt.find(pre + k - i);
		
		if(it != cnt.end()) {
			auto& S = it->second;
			auto k = S.lower_bound(make_pair(pre + 1, 0));
			if(k != S.end()) ans += (int)S.size() - S.order_of_key(*k);
		}
		
		cnt[pre - i].insert(make_pair(pre, i));
	}
	
	cout << ans << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
  //cin >> t;
    while(t--) solve();
    return 0;
}
