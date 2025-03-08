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

const int maxn = 1e5;
int N, Q, K, pai[maxn], pos[maxn], st[18][maxn];
ii X[maxn];

int query(int, int);
void solve(int, int, int);

int query(int L, int R) {
	int z = 31 - __builtin_clz(R - L + 1);
	return min(st[z][L], st[z][R - (1 << z) + 1]);
}

void solve(int root, int lo, int hi) {
	int k = pos[root];
	if(k < hi) {
		int dir = query(k + 1, hi);
		pai[dir] = X[k].first;
		solve(dir, k + 1, hi);
	}
	if(k > lo) {
		int esq = query(lo, k - 1);
		pai[esq] = X[k].first;
		solve(esq, lo, k - 1);
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 0; i < N; ++i) {
		cin >> X[i].first;
		X[i].second = i;
	}	
	sort(X, X + N);
	for(int i = 0; i < N; ++i) {
		pos[X[i].second] = i;
		st[0][i] = X[i].second;
	}
	K = 31 - __builtin_clz(N);
	for(int i = 1; i <= K; ++i)
		for(int k = 0; k + (1 << i) - 1 < N; ++k)
			st[i][k] = min(st[i - 1][k], st[i - 1][k + (1 << i - 1)]);
	solve(0, 0, N - 1);
	cin >> Q;
	while(Q--) {
		int x;	
		cin >> x;
		cout << pai[x - 1];
		if(Q) cout << ' ';
	}
	cout << '\n';
	return 0;
}