#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree <int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
using namespace std;
using namespace __gnu_pbds;
const int MAXN = 2e5 + 1;
class BIT {
	int ft[MAXN], n;
	public:
	BIT(int n) {
		this->n = n;
		memset(ft, 0, (n + 1) * sizeof(int));
	}
	int query(int k) {
		int ans = 0;
		while(k > 0) {
			ans += ft[k];
			k -= k & -k;
		}
		return ans;
	}
	int query(int l, int r) {
		return query(r) - query(l - 1);
	}
	void update(int k, int x) {
		while(k <= n) {
			ft[k] += x;
			k += k & -k;
		}
	}
};
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int n;	
	pair<int, int> y[MAXN];
	cin >> n;
	BIT bit(n);
	for(int i = 0; i < n; ++i) {
		bit.update(i + 1, 1);
		cin >> y[i].first;
		y[i].second = i + 1;
	}
	sort(y, y + n);
	long long cnt = 0;
	for(int i = 0; i < n; ++i) {
		int k = y[i].second;
		cnt += min(bit.query(k - 1), bit.query(k + 1, n));
		bit.update(k, -1);
	}
	cout << cnt << '\n';
	return 0;
}
