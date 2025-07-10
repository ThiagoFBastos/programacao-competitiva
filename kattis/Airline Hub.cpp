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

void t(double la, double lo, double& x, double& y, double& z) {
	la = M_PI * la / 180;
	lo = M_PI * lo / 180;
	z = sin(la);
	x = cos(la) * cos(lo);
	y = cos(la) * sin(lo);
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	double p[1000][3], loc[1000][2];	
	int n;
	cout.precision(2);
	cout.setf(ios_base :: fixed);
	for(; cin >> n;) {
		pair<double, int> pp = {INT_MAX + 0.0, -1};
		for(int i = 0; i < n; ++i) {
			for(int k = 0; k < 2; ++k) cin >> loc[i][k];
			t(loc[i][0], loc[i][1], p[i][0], p[i][1], p[i][2]);
		}
		for(int i = 0; i < n; ++i) {
			double dist = -1;
			for(int k = 0; k < n; ++k) dist = max(dist, sqrt(pow(p[i][0] - p[k][0], 2) + pow(p[i][1] - p[k][1], 2) + pow(p[i][2] - p[k][2], 2)));							
			pp = min(pp, make_pair(dist, -i));
		}
		cout << loc[-pp.second][0] << ' ' << loc[-pp.second][1] << '\n';
	}
    return 0;
}