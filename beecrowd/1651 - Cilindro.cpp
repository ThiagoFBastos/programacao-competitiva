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

double cilindro(double r, double h) {
	return M_PI * r * r * h;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int w, h;
	while(true) {
		cin >> w >> h;
		if(w == 0 && h == 0) break;
		if(w > h) swap(w, h);
		cout.precision(3);
		cout.setf(ios_base :: fixed);
		double a, b;
		a = w / (2 * M_PI);
		b = min(w / 2.0, h / (2 * M_PI + 2));
		cout << max(cilindro(b, w), cilindro(min(h / 3.0, a), h - 2 * min(h / 3.0, a))) << '\n'; 
	}
	return 0;
}