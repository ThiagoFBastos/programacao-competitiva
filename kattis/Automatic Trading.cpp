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
const int mod_1 = 1e9 + 7, mod_2 = 1e9 + 9;
int query(int, int, vi&, vi&, int, int);
int query(int l, int r, vi& m, vi& p, int n, int mod) {
	int res = 1LL * p[n - (l + 1)] * (m[r + 1] - m[l]) % mod;
	return res + (res < 0 ? mod : 0);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	int q;
	cin >> s >> q;
	vi m1(s.size() + 1), m2(s.size() + 1), p1(s.size() + 1), p2(s.size() + 1);
	m1[0] = m2[0] = 0;
	p1[0] = p2[0] = 1;
	for(int k = 1; k <= (int)s.size(); ++k) {
		p1[k] = p1[k - 1] * 88799LL % mod_1;
		p2[k] = p2[k - 1] * 7703LL % mod_2;
		m1[k] = (m1[k - 1] + 1LL * s[k - 1] * p1[k]) % mod_1;
		m2[k] = (m2[k - 1] + 1LL * s[k - 1] * p2[k]) % mod_2;
	}
	while(q--) {
		int l, r;
		cin >> l >> r;
		if(s[l] != s[r]) cout << "0\n";
		else {
			int lo = 1, hi = (int)s.size() - r;
			while(lo < hi) {
				int mid = (lo + hi) / 2;
				int h1, h2, h3, h4;
				h1 = query(l, l + mid, m1, p1, s.size(), mod_1);
				h2 = query(l, l + mid, m2, p2, s.size(), mod_2);
				h3 = query(r, r + mid, m1, p1, s.size(), mod_1);
				h4 = query(r, r + mid, m2, p2, s.size(), mod_2);
				if(h1 != h3 || h2 != h4) hi = mid;
				else lo = mid + 1; 
			}
			cout << hi << '\n';
		}
	}
	return 0;
}

