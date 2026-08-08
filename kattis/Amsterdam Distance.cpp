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

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int M, N;	
	int ax, ay, bx, by;
	double H, dist = INT_MAX, R;
	cin >> M >> N >> R;
	cin >> ax >> ay >> bx >> by;
	H = R / N;
	if(ay < by) {
		swap(ax, bx);
		swap(ay, by);
	}
	for(int y = by; y >= 0; --y)
		dist = min(dist, H * (by + ay - 2 * y + M_PI * y * abs(ax - bx) / M));
	cout << fixed << setprecision(15) << dist << '\n';
    return 0;
}