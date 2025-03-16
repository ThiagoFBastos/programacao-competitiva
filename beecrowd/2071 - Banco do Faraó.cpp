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

const ll INF = 1e10;

struct Info {
	ll sum_max, sum, preffix_max, suffix_max, n_preffix, n_suffix, n_sum_max, size;
	Info() {
		sum_max = sum = preffix_max = suffix_max = -INF;
		n_suffix = n_preffix = n_sum_max = size = 0;
	}
	Info(int x) {
		sum_max = sum = preffix_max = suffix_max = x;
		n_suffix = n_preffix = n_sum_max = size = 1;
	}
};

class segtree {

	vector<Info> st;
	int n;

	void combine(Info& dest, Info& left_info, Info& right_info) {

		dest.sum_max = left_info.sum_max;
		dest.n_sum_max = left_info.n_sum_max;
		dest.sum = left_info.sum + right_info.sum;
		dest.size = left_info.size + right_info.size;

		if(left_info.preffix_max > left_info.sum + right_info.preffix_max) {
			dest.preffix_max = left_info.preffix_max;
			dest.n_preffix = left_info.n_preffix;
		}

		else {
			dest.preffix_max = left_info.sum + right_info.preffix_max;
			dest.n_preffix = left_info.size + right_info.n_preffix;
		}

		if(right_info.suffix_max > right_info.sum + left_info.suffix_max) {
			dest.suffix_max = right_info.suffix_max;
			dest.n_suffix = right_info.n_suffix;
		}
		
		else {
			dest.suffix_max = right_info.sum + left_info.suffix_max;
			dest.n_suffix = right_info.size + left_info.n_suffix;
		}

		if(dest.sum_max < right_info.sum_max) {
			dest.sum_max = right_info.sum_max;
			dest.n_sum_max = right_info.n_sum_max;
		}

		else if(dest.sum_max == right_info.sum_max)
			dest.n_sum_max = max(dest.n_sum_max, right_info.n_sum_max);

		if(dest.sum_max < left_info.suffix_max + right_info.preffix_max) {
			dest.sum_max = left_info.suffix_max + right_info.preffix_max;
			dest.n_sum_max = left_info.n_suffix + right_info.n_preffix;
		}

		else if(dest.sum_max == left_info.suffix_max + right_info.preffix_max)
			dest.n_sum_max = max(dest.n_sum_max, left_info.n_suffix + right_info.n_preffix);
	}

	void build(vi& a, int l, int r, int no = 1) {
		if(l == r)
			st[no] = Info(a[l]);
		else {
			int mid = (l + r) >> 1;
			int L = no << 1, R = (no << 1) | 1;

			build(a, l, mid, L);
			build(a, mid + 1, r, R);

			combine(st[no], st[L], st[R]);
		}
	}

	void query(Info& info, int l, int r, int low, int high, int no = 1) {
		if(l > r) return ;

		else if(r - l == high - low)
			info = st[no];
		
		else {
			int mid, L = no << 1, R = (no << 1) | 1;
			Info left_info, right_info;

			mid = (low + high) >> 1;

			query(left_info, l, min(r, mid), low, mid, L);
			query(right_info, max(l, mid + 1), r, mid + 1, high, R);
			
			combine(info, left_info, right_info);			
		}
	}
	
	public:
	segtree(vi& a) {
		st.resize((1 << (33 - __builtin_clz(a.size()))));
		n = a.size();
		build(a, 0, n - 1);
	}
	void query(int l, int r, int& soma, int& k) {
		Info info;
		query(info, l, r, 0, n - 1);
		soma = info.sum_max;
		k = info.n_sum_max;
	}
};
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, q;
		cin >> n;
		vi a(n);
		for(int i = 0; i < n; ++i) cin >> a[i];
		segtree st(a);
		cin >> q;
		while(q--) {
			int l, r, soma, k;
			cin >> l >> r;
			--l , --r;
			st.query(l, r, soma, k);
			cout << soma << ' ' << k << '\n';
		}
	}
	return 0;
}