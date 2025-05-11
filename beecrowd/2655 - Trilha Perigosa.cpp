#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

int next_p(int n) {
	return 1 << (32 - __builtin_clz(n));
}

class segtree {
	vector<long long> st;
	int n;
	public:
	segtree(vector<int>& x) {
		n = next_p(x.size());
		st.assign(2 * n, 0);
		for(int i = n; i < st.size(); ++i) st[i] = 1LL << x[i - n];
		for(int i = n - 1; i > 0; --i) st[i] = st[2 * i] | st[2 * i + 1];
	}
	int query(int l, int r) {
		long long res = 0;
		l += n;
		r += n;
		while(l <= r) {
			if(l & 1) res |= st[l++];
			if(!(r & 1)) res |= st[r--];
			l >>= 1;
			r >>= 1;
		}
		return __builtin_popcountll(res);
	}
	void update(int k, int x) {
		k += n;
		st[k] = 1LL << x;
		k >>= 1;
		while(k > 0) {
			st[k] = st[2 * k] | st[2 * k + 1];
			k >>= 1;
		}
	}
};
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q, m;
	cin >> n >> q >> m;
	vector<int> x(next_p(n));
	for(int i = 0; i < n; ++i) {
		cin >> x[i];
		--x[i];	
	}
	segtree st(x);
	while(q--) {
		int t, a, b;
		cin >> t >> a >> b;
		--a, --b;
		if(t == 1) cout << st.query(a, b) << '\n';
		else st.update(a, b);
	}
	return 0;
}