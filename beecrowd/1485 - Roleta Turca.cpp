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
int m[250], b[125], dp[125][250][250];
static int modulo(int x, int m);
int modulo(int x, int m) {
	return x >= m ? x - m : x;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int INF = 1e9;
	int S, B;
	while(true) {
		cin >> S >> B;
		if(S == 0 && B == 0) break;
		for(int i = 0; i < B; ++i)
			for(int k = 0; k < S; ++k)
				for(int j = 0; j < S; ++j)
					dp[i][k][j] = -INF;
		for(int i = 0; i < S; ++i) 
			cin >> m[i];
		for(int i = 0; i < B; ++i) 
			cin >> b[i];
		for(int i = 0; i < S; ++i) 
			dp[0][i][i] = -(m[i] + m[modulo(i - 1 + S,  S)]) * b[0];
		for(int i = 1; i < B; ++i) {
			for(int L = 0; L < S; ++L) {
				int maxdp1 = dp[i - 1][L][L], maxdp2 = dp[i - 1][L][modulo(L + 1, S)];
				for(int R = modulo(L + 2, S), k = 1; k <= S - 3; R = modulo(R + 1, S), ++k) {
					dp[i][L][R] = max(dp[i][L][R], maxdp1 - (m[R] + m[modulo(R - 1 + S, S)]) * b[i]);
					maxdp1 = max(maxdp1, maxdp2);
					maxdp2 = max(maxdp2, dp[i - 1][L][R]);
				}
			}
		}
		int ans = -INF;
		for(int L = 0; L < S; ++L) 
			for(int R = 0; R < S; ++R) 
				ans = max(ans, dp[B - 1][L][R]);
		cout << ans << '\n';
	}
 	return 0;
}