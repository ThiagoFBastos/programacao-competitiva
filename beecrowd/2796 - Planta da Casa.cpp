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

const int maxn = 1e3 + 1;
int r, c, q, altura[maxn], esq[maxn], dir[maxn], largura[maxn];
vector<string> grid;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> r >> c;
	grid.resize(r);
	for(string& s : grid)	
		cin >> s;
	for(int k = 0; k < r; ++k) {
		deque<ii> S;
		for(int i = 0; i < c; ++i) {
			if(grid[k][i] == '#') 
				altura[i] = 0;
			else 
				++altura[i];
			while(!S.empty() && S.back().first > altura[i]) S.pop_back();
			if(S.empty())
				esq[i] = 0;
			else {
				if(S.back().first == altura[i])
					esq[i] = esq[S.back().second];
				else
					esq[i] = 1 + S.back().second;
			}
			S.push_back({altura[i], i});
		}
		S.clear();
		for(int i = c - 1; i >= 0; --i) {
			while(!S.empty() && S.back().first > altura[i]) S.pop_back();
			if(S.empty())
				dir[i] = c - 1;
			else {
				if(S.back().first == altura[i])
					dir[i] = dir[S.back().second];
				else
					dir[i] = S.back().second - 1;
			}
			largura[dir[i] - esq[i] + 1] = max(largura[dir[i] - esq[i] + 1], altura[i]);
			S.push_back({altura[i], i});
			
		}
	}
	for(int k = 999; k >= 0; --k) 
		largura[k] = max(largura[k], largura[k + 1]);
	cin >> q;
	ii ret = {0, 0};
	while(q--) {
		int w, h;
		cin >> w >> h;
		if(largura[w] >= h or largura[h] >= w) {
			if(ret.first * ret.second < w * h) ret = {h, w};
			else if(ret.first * ret.second == w * h) ret = max(ret, make_pair(h, w));
		}
	}
	cout << ret.second << ' ' << ret.first << '\n';
	return 0;
}