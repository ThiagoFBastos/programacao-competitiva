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
const int maxn = 1e5 + 1, maxb = 317;
int a[maxn], buckets[maxn][maxb], b[maxn];
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q, x;
	cin >> n >> q;
	x = 1 + (int)sqrt(n);
	for(int k = 0; k < maxn; ++k)
		for(int i = 0; i < x; ++i)
			buckets[k][i] = 0;
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		b[i] = i / x;
		++buckets[a[i]][b[i]];
	}
	while(q--) {
		int t, X, Y, Z;
		cin >> t >> X >> Y;
		--X;
		if(t == 2) {
			--Y;
			cin >> Z;
			int l = b[X], r = b[Y], cnt = Y - X + 1;
			for(int k = X; k <= min(x + l * x - 1, Y); ++k) if(a[k] == Z) --cnt;
			if(l != r) for(int k = Y; k >= r * x; --k) if(a[k] == Z) --cnt;
			++l, --r;
			while(l <= r) {
				cnt -= buckets[Z][l];
				++l;
			}
			cout << cnt << '\n';
		}
		else {
			int k = b[X];
			--buckets[a[X]][k];
			++buckets[Y][k];
			a[X] = Y;
		}
	}
	return 0;
}