#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		a[i] += i;
	}
	for(int i = 0; i < n; ++i) {
		cin >> b[i];
		b[i] += i;
	}
	auto cmp = [](auto a, auto b) {
		sort(all(a));	
		sort(all(b));
		return a == b;
	};
	if(!cmp(a, b)) {
		cout << "-1\n";
		return;
	}
	map<int, vector<int>> mp;
	ordered_set<int> os;
	i64 swaps = 0;
	for(int i = n - 1; i >= 0; --i) {
		mp[a[i]].pb(i);
		os.insert(i);	
	}
	for(int i = 0; i < n; ++i) {
		auto& P = mp[b[i]];
		int k = P.back(); P.pop_back();
		swaps += os.order_of_key(k);
		os.erase(k);
	}
	cout << swaps << '\n';
}
	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
