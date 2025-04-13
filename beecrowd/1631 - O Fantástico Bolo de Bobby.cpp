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
#define x first
#define y second
#define dx real()
#define dy imag()
#define eps 1e-9
using Vector = complex<double>;

Vector dir(ii& a, ii& b) {
	return {b.x - a.x, b.y - a.y};
}
int sig(double x) {
	return x > eps ? 1 : (x < -eps ? -1 : 0);
}
int side(ii& a, ii& b, ii& c) {
	Vector u = dir(a, b);
	Vector v = dir(a, c);
	return sig((conj(u)*v).dy);
}

double dist(ii& a, ii& b, ii& c) {
	Vector u = dir(a, b);
	Vector v = dir(a, c);
	return abs((conj(u)*v).dy) / abs(u);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cout.precision(3);
	cout.setf(ios_base :: fixed);
	while(true) {
		cin >> n;
		if(n == 0) break;
		vii p(n);
		double S = 1e9;
		for(int i = 0; i < n; ++i)
			cin >> p[i].x >> p[i].y;
		for(int i = 0; i < n; ++i) {
			for(int k = i + 1; k < n; ++k) {
				double e = 0, d = 0;
				for(int j = 0; j < n; ++j) {
					int l = side(p[i], p[k], p[j]);
					if(l == 1) d += dist(p[i], p[k], p[j]);
					else e += dist(p[i], p[k], p[j]);
				}
				S = min(abs(e - d), S);
			}
		}
		cout << S << '\n';
	}
	return 0;
}