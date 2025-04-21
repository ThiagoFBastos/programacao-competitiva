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

const int maxn = 1e6 + 1100;
int p[maxn], N, M, lst, last[maxn];
bool win;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int k = 1; k <= N; ++k) {
		p[k] += p[k - 1];
		if(k - lst > M) lst = 0;
		win = false;
		if(p[k] < min(M, k)) {
			win = true;
			++p[k + 1];
			if(p[k] == min(M, k) - 1) {
				if(k - lst <= M)
					last[k] = k - lst;
				--p[k + last[k]];
				++p[k + last[k] + 1];
				last[k + last[k]] = last[k];
			}
			--p[k + M + 1];
		} else if(p[k] == M)
			lst = k;
	}
	cout << (win ? "Paula\n" : "Carlos\n");
	return 0;
}