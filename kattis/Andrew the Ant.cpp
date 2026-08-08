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
	int L, A;
	while(cin >> L >> A) {
		vector<pair<int, char>> a(A);
		int ans = 0;
		for(int i = 0; i < A; ++i) {
			cin >> get<0>(a[i]) >> get<1>(a[i]);
			ans = max(ans, get<1>(a[i]) == 'L' ? get<0>(a[i]) : L - get<0>(a[i]));
		}
		sort(a.begin(), a.end());
		int p = -1, q = -1;
		for(int i = 0; i < A; ++i) {
			if(get<1>(a[i]) == 'L' && ans == get<0>(a[i])) {
				queue<int> S;
				p = get<0>(a[i]);
				for(int k = i - 1; k >= 0; --k) {
					if(get<1>(a[k]) == 'R') {
						S.push(get<0>(a[k]));
						p = S.front();
						S.pop();
					} else
						S.push(get<0>(a[k]));
				}
				break;
			}
		}
		for(int i = 0; i < A; ++i) {
			if(get<1>(a[i]) == 'R' && ans == L - get<0>(a[i])) {
				queue<int> S;
				q = get<0>(a[i]);
				for(int k = i + 1; k < A; ++k) {
					if(get<1>(a[k]) == 'L') {
						S.push(get<0>(a[k]));
						q = S.front();
						S.pop();
					} else
						S.push(get<0>(a[k]));
				}
				break;
			}
		}
		cout << "The last ant will fall down in " << ans << " seconds - started at ";
		if(p != -1 && q != -1) cout << p << " and " << q << ".\n";
		else cout << max(p, q) << ".\n";
	}
	return 0;
}

