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

class segtree {
	vi st, lv;
	int n;
	public:
	segtree(vi& data) {
		n = 1 << (32 - __builtin_clz(data.size()));
		st.resize(n << 1);
		lv.resize(n << 1);	
		for(int k = n; k < st.size(); ++k) {
			st[k] = k < n + data.size() ? data[k - n] : 0;
			lv[k] = 0;
		}
		for(int no = n - 1; no; --no) {
			lv[no] = 1 ^ lv[no << 1];
			st[no] = lv[no] ? st[no << 1] + st[(no << 1) | 1] : st[no << 1] - st[(no << 1) | 1];
		}
	}
	int query() {
		return st[1];
	}
	void update(int no, int x) {
		no += n;
		st[no] = x;
		no >>= 1;
		while(no) {
			st[no] = lv[no] ? st[no << 1] + st[(no << 1) | 1] : st[no << 1] - st[(no << 1) | 1];
			no >>= 1;
		}
	}
};

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t, f = 1;
	cin >> t;
	while(t--) {
		int n, q;
		cin >> n >> q;
		vi a(n);
		for(int i = 0; i < n; ++i) cin >> a[i];
		segtree st(a);
		cout << st.query() << ' ';
		if(st.query() & 1) cout << (f ? "Rusa\n" : "Sanches\n");
		else cout << (f ? "Sanches\n" : "Rusa\n");
		while(q--) {
			int k, x;
			cin >> k >> x;
			st.update(k - 1, x);
			cout << st.query() << ' ';
			if(st.query() & 1) cout << (f ? "Rusa\n" : "Sanches\n");
			else  cout << (f ? "Sanches\n" : "Rusa\n");			
		}
		f ^= 1;
	}
	return 0;
}