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
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

const int maxn = 1e5 + 1;
int n, q, R[maxn][2], C[maxn][2], cnt[51];
ordered_set<int> XR[51], XC[51];

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> q;

	for(int i = 0; i <= n; ++i) {
		R[i][0] = R[i][1] = 0;
		C[i][0] = C[i][1] = 0;
	}
	
	for(int t = 1; t <= q; ++t) {

		int type, X, arg;

		cin >> type >> X;

		if(type == 1) {
			cin >> arg;
			if(R[X][0]) XR[R[X][1]].erase(R[X][0]);
			XR[arg].insert(t);
			R[X][0] = t, R[X][1] = arg;
		} else if(type == 2) {
			cin >> arg;
			if(C[X][0]) XC[C[X][1]].erase(C[X][0]);
			XC[arg].insert(t);
			C[X][0] = t, C[X][1] = arg;
		} else if(type == 3) {
			int ans = 0, fm = 0;		
			memset(cnt, 0, sizeof cnt);
			cnt[R[X][1]] += n;
			for(int i = 0; i <= 50; ++i) {
				int f = (int)XC[i].size() - XC[i].order_of_key(R[X][0]);
				cnt[R[X][1]] -= f;
				cnt[i] += f;
			}
			for(int i = 50; i >= 0; --i) {
				if(fm < cnt[i])
					fm = cnt[i], ans = i;
			}
			cout << ans << '\n';
		} else {
			int ans = 0, fm = 0;		
			memset(cnt, 0, sizeof cnt);
			cnt[C[X][1]] += n;
			for(int i = 0; i <= 50; ++i) {
				int f = (int)XR[i].size() - XR[i].order_of_key(C[X][0]);
				cnt[C[X][1]] -= f;
				cnt[i] += f;
			}
			for(int i = 50; i >= 0; --i) {
				if(fm < cnt[i])
					fm = cnt[i], ans = i;
			}
			cout << ans << '\n';
		}
	}

	return 0;
}