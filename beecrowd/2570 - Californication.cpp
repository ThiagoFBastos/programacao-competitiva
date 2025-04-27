#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
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
const int maxn = 1001;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	int r[maxn][2], c[maxn][2];	
	cin >> n >> m >> k;
	memset(&r[0][0], -1, sizeof r);
	memset(&c[0][0], -1, sizeof c);
	for(int i = 0; i < k; ++i) {
		char t;
		int a;
		cin >> t >> a;
		if(t == 'L') {
			r[a][0] = i;
			r[a][1] = i & 3;
		}
		else {
			c[a][0] = i;
			c[a][1] = i & 3;
		}
	}
	int cnt[4] = {0};
	for(int a = 1; a <= n; ++a) {
		for(int b = 1; b <= m; ++b) {
			if(r[a][0] == -1 && c[b][0] == -1) continue;
			++cnt[r[a][0] > c[b][0] ? r[a][1] : c[b][1]];
		}
	}
	cout << 'R' << cnt[0] << ' ' << 'H' << cnt[1] << ' ' << 'C' << cnt[2] << ' ' << 'P' << cnt[3] << '\n';
	return 0;
}