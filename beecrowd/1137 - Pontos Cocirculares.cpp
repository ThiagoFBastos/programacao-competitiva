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

#define f first
#define s second
#define eps 1e-9

struct Circle {
	double a, b, r;
};

int sig(double x) {
	return x > eps ? 1 : (x < -eps ? -1 : 0);
}

bool operator<(Circle c1, Circle c2);
static double det(double a, double b, double c, double d);
static bool get_circle(Circle& ci, ii& a, ii& b, ii& c);

bool operator<(Circle c1, Circle c2) {
	return sig(c1.a - c2.a) < 0 || sig(c1.a - c2.a) == 0 && sig(c1.b - c2.b) < 0 || sig(c1.a - c2.a) == 0 && sig(c1.b - c2.b) == 0 && sig(c1.r - c2.r) < 0;
}

double det(double a, double b, double c, double d) {
	return a * d - b * c;
}

bool get_circle(Circle& ci, ii& a, ii& b, ii& c) {
	double x, y, a1, b1, a2, b2;
	x = (b.f * b.f + b.s * b.s - a.f * a.f - a.s * a.s) / 2.0;
	y = (c.f * c.f + c.s * c.s - b.f * b.f - b.s * b.s) / 2.0;
	a1 = b.f - a.f;
	b1 = b.s - a.s;
	a2 = c.f - b.f;
	b2 = c.s - b.s;
	double d = det(a1, b1, a2, b2);
	if(sig(d) == 0) return false;
	ci.a = det(x, b1, y, b2) / d;
	ci.b = det(a1, x, a2, y) / d;
	ci.r = pow(a.f - ci.a, 2) + pow(a.s - ci.b, 2);
	return true;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	while(true) {
		cin >> n;
		if(n == 0) break;
		vii p(n);
		for(int i = 0; i < n; ++i)
			cin >> p[i].f >> p[i].s;
		map<Circle, bitset<100>> S;  
		bitset<100> x;
		for(int i = 0; i < n; ++i) {
			for(int k = i + 1; k < n; ++k) {
				for(int j = k + 1; j < n; ++j) {
					Circle c;
					if(get_circle(c, p[i], p[k], p[j])) {
						x[i] = x[k] = x[j] = 1;
						S[c] |= x;
						x[i] = x[k] = x[j] = 0;
					}
				}
			}
		}
		int res = 1;
		if(n > 1) res = 2;
		for(auto &[c, b] : S)
			res = max<int>(res, b.count());
		cout << res << '\n';
	}
	return 0;
}