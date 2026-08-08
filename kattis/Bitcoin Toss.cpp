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
	int t, cnt[10][1 << 10], p[10], lo[10], f[10], l[10];
	vi R[10];
	cin >> t;
	while(t--) {
		string s;
		cin >> s;
		for(char& c : s) c = c == 'T' ? '1' : '0';
		int maxn = 0, first_pos = INT_MAX;
		for(int k = 1; k <= 10; ++k) {
			if((k << k) > (int)s.size()) break;	
			int fpos = INT_MAX, n = 1 << k;
			for(int i = 0; i < k; ++i) {
				R[i].clear();
				lo[i] = p[i] = l[i] = 0;
				f[i] = n;
				for(int j = 0; j < n; ++j)
					cnt[i][j] = 0;
			}
			for(int i = 0; i < (int)s.size(); ++i) {
				for(int j = 0; j < min(k, i + 1); ++j) {
					p[j] = (p[j] << 1) | (s[i] - '0');
					if(++l[j] == k) {
						if(++cnt[j][p[j]] > 1) {
							while(lo[j] < (int)R[j].size() && cnt[j][p[j]] > 1) {
								++f[j];
								--cnt[j][R[j][lo[j]]];
								++lo[j];
							}
						}
						if(--f[j] == 0) fpos = min(fpos, i - (k << k) + 1);
						R[j].push_back(p[j]);
						p[j] = l[j] = 0;
					}
				}
			}
			if(fpos != INT_MAX) maxn = k, first_pos = fpos;
		}
		cout << maxn << ' ' << first_pos << '\n';
	}
	return 0;
}