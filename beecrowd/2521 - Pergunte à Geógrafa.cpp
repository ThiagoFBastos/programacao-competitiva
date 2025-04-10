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


int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int r, la, lo;
	cout.setf(ios_base :: fixed);
	cout.precision(2);
	while(cin >> r >> la >> lo) {
		int x, y, z;
		x = round(100 * r * cos(la * M_PI / 180.0) * sin(lo * M_PI / 180.0));
		y = round(100 * r * sin(la * M_PI / 180.0));
		z = round(100 * cos(la * M_PI / 180.0) * cos(lo * M_PI / 180.0) * r);
		cout << x / 100.0 << ' ' << y / 100.0 << ' ' << -z / 100.0 << '\n';
	}
    return 0;
}