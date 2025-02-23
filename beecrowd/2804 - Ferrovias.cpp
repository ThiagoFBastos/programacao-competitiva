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

const int maxn = 450;
int g[maxn][maxn], n, p, custo;
bool ok = true;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> p;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			cin >> g[i][j];
	for(int i = 0; i < n; ++i) {
		if(g[i][i]) {
			ok = false;
			goto fim;
		}
		for(int j = 0; j < n; ++j) {
			if(g[i][j] != g[j][i]) {
				ok = false;
				goto fim;
			}
		}
	}
	for(int a = 0; a < n; ++a) {
		for(int b = a + 1; b < n; ++b) {
			int cnt = 1;
			for(int c = 0; c < n; ++c) {
				if(c == a || c == b) continue;
				else if(g[c][a] + g[c][b] < g[a][b]) {
					ok = false;
					goto fim;
				} else if(g[c][a] + g[c][b] == g[a][b]) {
					cnt = 0;
					break;
				}
			}
			custo += cnt;
		}
	}
	fim:
	if(ok) cout << custo * p << '\n';
	else cout << "*\n";
	return 0;
}