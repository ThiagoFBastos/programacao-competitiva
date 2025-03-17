#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree <int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
using namespace std;
using namespace __gnu_pbds;
const int MOD = 1e9 + 7;
int main() {
	int n, q, dp1[100][100], dp2[100];	
	char s[101];
	while(scanf("%d", &n) != EOF) {
		unordered_set<string> S;
		S.reserve(n);
		for(int i = 0; i < n; ++i) {
			scanf("%s", s);
			S.insert(s);
		}
		scanf("%d", &q);
		while(q--) {
			int m;
			scanf("%s", s);
			m = strlen(s);
			memset(dp2, 0, sizeof(int) * m);
			for(int k = 0; k < m; ++k)
				for(int i = 0; i < m; ++i)
					dp1[k][i] = 0;
			for(int L = 1; L <= m; ++L) {
				for(int k = 0; k <= m - L; ++k) {
					char c = s[k + L];
					s[k + L] = '\0';
					dp1[k][k + L - 1] = S.count(s + k);
					s[k + L] = c; 
				}
			}
			for(int i = 0; i < m; ++i)
				dp2[i] = dp1[i][m - 1];
			for(int i = m - 1; i >= 0; --i)
				for(int k = i + 1; k < m; ++k)
					dp2[i] = (dp2[i] + 1LL * dp2[k] * dp1[i][k - 1]) % MOD;
			printf("%d\n", dp2[0]);
		}
	}
	return 0;
}