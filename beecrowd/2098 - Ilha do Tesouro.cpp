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
const int maxn = 500;
int h[maxn][maxn], t[maxn][maxn], r, c;
bool has_path(int tt) {
	if(h[0][0] <= tt) return false;
	for(int k = 0; k < r; ++k)
		for(int i = 0; i < c; ++i)
			t[k][i] = -1;
	t[0][0] = tt;
	queue<ii> s;
	s.push({0, 0});
	while(!s.empty()) {
		auto [x, y] = s.front();
		s.pop();
		if(x == r - 1 && y == c - 1) return true;
		if(x && t[x - 1][y] == -1 && h[x - 1][y] > 1 + t[x][y]) {
			t[x - 1][y] = 1 + t[x][y];
			s.push({x - 1, y});
		}
		if(x < r - 1 && t[x + 1][y] == -1 && h[x + 1][y] > 1 + t[x][y]) {
			t[x + 1][y] = 1 + t[x][y];
			s.push({x + 1, y});
		}
		if(y && t[x][y - 1] == -1 && h[x][y - 1] > 1 + t[x][y]) {
			t[x][y - 1] = 1 + t[x][y];
			s.push({x, y - 1});
		}
		if(y < c - 1 && t[x][y + 1] == -1 && h[x][y + 1] > 1 + t[x][y]) {
			t[x][y + 1] = 1 + t[x][y];
			s.push({x, y + 1});
		}
	}
	return false;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int max_h = 0;
	cin >> r >> c;
	for(int k = 0; k < r; ++k) {
		for(int i = 0; i < c; ++i) {
			cin >> h[k][i];
			max_h = max(h[k][i], max_h);
		}
	}
	if(has_path(0)) {
		int tt = 0;
		for(int k = 31 - __builtin_clz(max_h); k >= 0; --k) {
			if((1 << k) + tt <= max_h && has_path((1 << k) + tt))
				tt |= 1 << k;
		}
		cout << tt << '\n';
	} else cout << "-1\n";
	return 0;
}