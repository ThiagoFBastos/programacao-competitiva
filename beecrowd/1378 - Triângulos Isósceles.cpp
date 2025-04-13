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

#define x first
#define y second
const int maxn = 1e3;
int n;
ii p[maxn];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(;;) {
		cin >> n;
		if(!n) break;
		for(int k = 0; k < n; ++k)
			cin >> p[k].x >> p[k].y;
		int cnt = 0;
		for(int k = 0; k < n; ++k) {
			unordered_map<ll, int> R;
			R.reserve(n);
			for(int i = 0; i < n; ++i) {
				ll d = (p[k].x - p[i].x + 0LL) * (p[k].x - p[i].x) + (p[k].y - p[i].y + 0LL) * (p[k].y - p[i].y);
				cnt += 2 * R[d]++;			
			}
		}
		cout << cnt / 2 << '\n';
	}
	return 0;
}