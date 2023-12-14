#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree <int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
using namespace std;
using namespace __gnu_pbds;
using matrix = array<array<int, 3>, 3>;
const int MAXN = 362880;
int S[MAXN], fat[9];
int F(matrix& src) {
	int mask = 511, y = 0;
	for(int k = 0, p = 1; k < 3; ++k) {
		for(int i = 0; i < 3; ++p, ++i) {
			int b;
			b = 1 << src[k][i];
			mask ^= b;
			y += fat[9 - p] * __builtin_popcount(mask & (b - 1));
		}
	}
	return y;
}
int solve(matrix& src) {
	queue<matrix> Q;
	memset(S, -1, sizeof S);
	S[F(src)] = 0;
	Q.push(src);
	while(!Q.empty()) {
		matrix m = Q.front();
		int z = F(m);
		if(z == 0) break;
		Q.pop();
		for(int k = 0; k < 3; ++k) {
			for(int i = 0; i < 3; ++i) {
				if(k) {
					matrix u = m;
					swap(u[k][i], u[k - 1][i]);
					int y = F(u);
					if(S[y] == -1) {
						S[y] = 1 + S[z];
						Q.push(u);
					}
				}
				if(i) {
					matrix u = m;
					swap(u[k][i], u[k][i - 1]);
					int y = F(u);
					if(S[y] == -1) {
						S[y] = 1 + S[z];
						Q.push(u);
					}
				}
			}
		}
	}
	return S[0];
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	matrix src;
	fat[0] = 1;
	for(int k = 1; k <= 8; ++k)
		fat[k] = k * fat[k - 1];
	for(int k = 0; k < 3; ++k) {
		for(int i = 0; i < 3; ++i) {
			cin >> src[k][i];
			--src[k][i];
		}
	}
	cout << solve(src) << '\n';
	return 0;
}
