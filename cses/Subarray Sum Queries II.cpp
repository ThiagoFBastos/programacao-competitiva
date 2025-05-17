#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 2e5 + 5;
 
struct node {
	int64_t prefix;
	int64_t suffix;
	int64_t sum;
	int64_t max_sum;
 
	node() = default;
	
	node(int64_t x) {
		prefix = suffix = max_sum = max<int64_t>(0, x); 
		sum = x;
	}
};
 
int a[N], n, q;
node st[4 * N];
 
node merge(node left, node right) {
	node no;
 
	no.prefix = max(left.prefix, left.sum + right.prefix);
	no.suffix = max(right.suffix, right.sum + left.suffix);
	no.sum = left.sum + right.sum;
	no.max_sum = max({left.max_sum, right.max_sum, left.suffix + right.prefix});
 
	return no;
}
 
void build(int l, int r, int p = 1) {
	if(l == r) {
		st[p] = node(a[l]);
		return;
	}
	
	int mid = (l + r) / 2;
 
	build(l, mid, 2 * p);
	build(mid + 1, r, 2 * p + 1);
 
	st[p] = merge(st[2 * p], st[2 * p + 1]);
}
 
node query(int l, int r, int lo, int hi, int p = 1) {
	if(r < lo || l > hi) return node(0);
	else if(l <= lo && hi <= r) return st[p];
 
	int mid = (lo + hi) / 2;
 
	auto left = query(l, r, lo, mid, 2 * p);
	auto right = query(l, r, mid + 1, hi, 2 * p + 1);
 
	return merge(left, right);
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n >> q;
	
	for(int i = 0; i < n; ++i)
		cin >> a[i];
 
	build(0, n - 1);
 
	while(q--) {
		int l, r;
 
		cin >> l >> r;
 
		auto ans = query(l - 1, r - 1, 0, n - 1);
 
		cout << ans.max_sum << '\n';
	}
 
	return 0;
}
