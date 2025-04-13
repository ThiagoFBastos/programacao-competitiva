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

double distseg(int x, int y, tuple<int, int, int, int> s) {
	complex<double> a, b, c;
	a = {get<2>(s) - get<0>(s), get<3>(s) - get<1>(s)};
	b = {x - get<0>(s), y - get<1>(s)};
	c = {x - get<2>(s), y - get<3>(s)};
	if((a * conj(b)).real() < 0 or (c * conj(-a)).real() < 0) 
		return min(abs(b), abs(c));
	return abs((a * conj(b)).imag()) / abs(a);	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cout.precision(2);
	cout.setf(ios_base :: fixed);
	while(cin >> n) {
		int L, H;
		cin >> L >> H;
		vector<tuple<int, int, int>> s(n);
		for(int k = 0; k < n; ++k) cin >> get<0>(s[k]) >> get<1>(s[k]) >> get<2>(s[k]);
		double d = INT_MAX;
		for(int k = 0; k < n; ++k) {
			if(k & 1) {
				d = min<double>(d, get<1>(s[k]));
				if(k < n - 1) d = min<double>(d, distseg(get<1>(s[k]), get<2>(s[k]), {0, get<0>(s[k + 1]), get<1>(s[k + 1]), get<2>(s[k + 1])}));
			} else {
				d = min<double>(d, L - get<1>(s[k]));
				if(k < n - 1) d = min<double>(d, distseg(get<1>(s[k]), get<2>(s[k]), {L, get<0>(s[k + 1]), get<1>(s[k + 1]), get<2>(s[k + 1])}));
			}
		}
		cout << d << '\n';
	}	
	return 0;
}