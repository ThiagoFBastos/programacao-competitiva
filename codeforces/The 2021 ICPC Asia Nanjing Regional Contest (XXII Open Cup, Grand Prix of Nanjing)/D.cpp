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

	vector<int> a(n), util(n + 1, 0);
	vector<ii> maxq;
	vector<i64> ps(n + 1, 0);
	ordered_set<int> os;
	int maxn = 0, frq = 0;

	for(int& v : a) cin >> v;

	for(int i = n - 1; i >= 0; --i) {
		while(!maxq.empty() && maxq.back().sc <= a[i]) maxq.pop_back();
		maxq.pb({i, a[i]});
	}

	reverse(all(maxq));

	for(int i = 1; i <= n; ++i) {
		int k = os.size() - os.order_of_key(a[i-1] + 1);

		ps[i] = ps[i - 1] + k;

		os.insert(a[i-1]);

		util[i] = util[i - 1] + (maxn > a[i - 1] && frq == 1);
		
		if(maxn < a[i - 1]) {
			frq = 1;
			maxn = a[i - 1];
		} else if(maxn == a[i - 1]) ++frq;
	}

	for(int i = 1; i <= n; ++i) {
		int k = lower_bound(maxq.begin(), maxq.end(), ii(i - 1, INF)) - maxq.begin();
		auto [j, x] = maxq[k - 1];
		i64 swaps = k - 1 + ps[i] - util[j+1] + j;
		cout << swaps;
		if(i==n)cout<<'\n';
		else cout << ' ';
	}
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
