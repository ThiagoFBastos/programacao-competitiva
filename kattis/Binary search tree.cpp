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

const int maxn = 3e5;
int N, st[19][maxn], sz;
vii a;
vi t;
vector<ll> ans;

void build() {
	sz = 31 - __builtin_clz(N);
	for(int k = 0; k < N; ++k) st[0][k] = a[k].second;
	for(int k = 1; k <= sz; ++k)
		for(int i = 0; i + (1 << k) - 1 < N; ++i)
			st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << k - 1)]);
}

int query(int l, int r) {
	int j = 31 - __builtin_clz(r - l + 1);
	return min(st[j][l], st[j][r - (1 << j) + 1]);
}

void solve(int k, int lv, int lo, int hi) {
	ans[a[k].second] += lv;
	if(k > lo) solve(t[query(lo, k - 1)], lv + 1, lo, k - 1);
	if(k < hi) solve(t[query(k + 1, hi)], lv + 1, k + 1, hi);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	a.resize(N);
	t.resize(N);
	ans.assign(N, 0);
	for(int i = 0; i < N; ++i) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a.begin(), a.end());
	for(int k = 0; k < N; ++k) t[a[k].second] = k;
	build();
	solve(t[query(0, N - 1)], 0, 0, N - 1);
	for(int k = 1; k < N; ++k) ans[k] += ans[k - 1];
	for(int k = 0; k < N; ++k) cout << ans[k] << '\n';
	return 0;
}