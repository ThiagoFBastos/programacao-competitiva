#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ordered_set tree <int, null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update>
const int MAXN = 2e5, MOD = 1e9 + 7;
int ft[MAXN + 1], m;
void update(int pos, int V) {
	while(pos <= m) {
		ft[pos] += V;
		if(ft[pos] >= MOD) ft[pos] -= MOD;
		pos += pos & -pos;
	}
}
int query(int pos) {
	int r = 0;
	while(pos > 0) {
		r += ft[pos];
		if(r >= MOD) r -= MOD;
		pos -= pos & -pos;
	}
	return r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ordered_set S;
	int n, a[MAXN];
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		S.insert(a[i]);
	}
	m = S.size();
	memset(ft, 0, (m + 1) * sizeof(int));
	for(int k = n - 1; k >= 0; --k) {
		int pos = S.order_of_key(a[k]);
		int l = query(pos + 1), r = query(m);
		update(pos + 1, (1 + r - l + MOD) % MOD);
	}
	cout << (query(m) + MOD) % MOD << '\n';
	return 0;
}
