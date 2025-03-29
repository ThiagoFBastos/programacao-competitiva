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

const int maxn = 3e5, maxb = 548;
int m[maxn], b[maxn], n_buckets, n, q, u;
ordered_multiset<int> buckets[maxb];

static int count(int, int, int);
static void update(int, int);

int count(int v, int L, int R) {
	int x = min((1 + b[L]) * n_buckets - 1, R);
	int cnt = 0;
	for(int k = L; k <= x; ++k) if(m[k] < v) ++cnt;
	if(b[L] != b[R]) {
		int y = n_buckets * b[R];
		for(int k = R; k >= y; --k) if(m[k] < v) ++cnt;
	}
	L = b[L] + 1;
	R = b[R] - 1;
	while(L <= R) {
		cnt += buckets[L].order_of_key(v);
		++L;
	}
	return cnt;
}

void update(int k, int x) {
	int j = b[k];
	buckets[j].erase(buckets[j].find_by_order(buckets[j].order_of_key(m[k])));
	buckets[j].insert(x);
	m[k] = x;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q >> u;
	n_buckets = 1 + (int)sqrt(n);
	for(int i = 0; i < n; ++i) {
		cin >> m[i];
		b[i] = i / n_buckets;
		buckets[b[i]].insert(m[i]);
	}
	while(q--) {
		int L, R, v, p;
		cin >> L >> R >> v >> p;
		--L, --R, --p;
		update(p, 1LL * u * count(v, L, R) / (R - L + 1));
	}
	for(int i = 0; i < n; ++i) cout << m[i] << '\n';
	return 0;
}