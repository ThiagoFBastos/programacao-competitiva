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

const int maxn = 1e5, maxb = 25;

int n, q, a[maxn], b[maxn], n_buckets;
ordered_multiset<int> buckets[maxb];

static int query(int L, int R, int x);
static void update(int k, int x);

int query(int L, int R, int x) {
	int l = b[L], r = b[R];
	int M = min(l * n_buckets + n_buckets - 1, R), N = r * n_buckets;
	int cnt = 0;
	for(int k = L; k <= M; ++k) if(a[k] > x) ++cnt;
	if(l != r) {
		for(int k = N; k <= R; ++k)
			if(a[k] > x) ++cnt;
	}
	++l, --r;
	while(l <= r) {
		cnt += buckets[l].size() - buckets[l].order_of_key(x + 1);
		++l;
	}
	return cnt;
}

void update(int k, int x) {
	int j = b[k];
	buckets[j].erase(buckets[j].find_by_order(buckets[j].order_of_key(a[k])));
	buckets[j].insert(x);
	a[k] = x;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	int K = 31 - __builtin_clz(n);
	n_buckets = (int)sqrt(n) * max(1, K);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		b[i] = i / n_buckets;
		buckets[b[i]].insert(a[i]);
	}
	while(q--) {
		int t, x, y, z;
		cin >> t >> x >> y;
		if(t == 1)
			update(x - 1, y);
		else {
			cin >> z;
			cout << query(y - 1, z - 1, x) << '\n';
		} 
	}
	return 0;
}