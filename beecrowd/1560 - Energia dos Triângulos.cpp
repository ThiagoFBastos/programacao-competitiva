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
using point = pair<double, double>;
int side(ii& a, ii& b, ii& c) {
	int z = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return z < 0 ? 0 : 1;
}
int side(ii& a, ii& b, point& c) {
	double z = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return z < 0 ? 0 : 1;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int maxn = 100;
	int n, m;
	bitset<maxn> S[2][maxn][maxn];
	ii b[maxn], w[maxn];	
	while(cin >> n >> m) {
		for(int i = 0; i < n; ++i) cin >> b[i].x >> b[i].y;
		for(int i = 0; i < m; ++i) cin >> w[i].x >> w[i].y;
		for(int i = 0; i < n; ++i) {
			for(int k = i + 1; k < n; ++k) {
				S[0][i][k].reset();
				S[1][i][k].reset();
			}
		}
		for(int i = 0; i < n; ++i) {
			for(int k = i + 1; k < n; ++k) {
				for(int j = 0; j < m; ++j) {
					int z = side(b[i], b[k], w[j]);
					S[z][i][k][j] = 1;
				}
			}
		}
		ll res = 0;
		for(int i = 0; i < n; ++i) {
			for(int k = i + 1; k < n; ++k) {
				for(int j = k + 1; j < n; ++j) {
					point ba;
					int X, Y, Z, cnt;
					ba.x = (b[i].x + b[k].x + b[j].x) / 3.0;
					ba.y = (b[i].y + b[k].y + b[j].y) / 3.0;
					X = side(b[i], b[k], ba);
					Y = side(b[i], b[j], ba);
					Z = side(b[k], b[j], ba);
					cnt = (S[X][i][k] & S[Y][i][j] & S[Z][k][j]).count();
					res += cnt * cnt; 
				}
			}
		}
		cout << res << '\n';
	}
	return 0;
}