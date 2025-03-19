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

const int maxn = 2e3 + 1, inf = 1e9;
int dp[maxn][maxn], n, m, nxtS[maxn][26], nxtT[maxn][26], last[26], ans = inf;
string s, t;
vi S[26], T[26];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> s >> t;
	for(int i = 0; i < n; ++i) S[s[i] - 'a'].push_back(i);
	for(int i = 0; i < m; ++i) T[t[i] - 'a'].push_back(i);
	for(int i = 0; i < n; ++i)
		for(int k = 0; k < m; ++k)
			dp[i][k] = inf;
	for(int i = 0; i < 26; ++i) {
		if(!S[i].empty() && T[i].empty()) {
			cout << 1 << '\n';
			return 0;
		}
		else if(S[i].empty() || T[i].empty()) continue;
		dp[S[i][0]][T[i][0]] = 1;
	}
	fill(last, last + 26, n);
	for(int i = n - 1; i >= 0; --i) {
		memcpy(nxtS[i], last, 26 * sizeof(int));
		last[s[i] - 'a'] = i;
	}
	fill(last, last + 26, m);
	for(int i = m - 1; i >= 0; --i) {
		memcpy(nxtT[i], last, 26 * sizeof(int));
		last[t[i] - 'a'] = i;
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(dp[i][j] == inf) continue;
			for(int k = 0; k < 26; ++k)
				dp[nxtS[i][k]][nxtT[j][k]] = min(dp[nxtS[i][k]][nxtT[j][k]], dp[i][j] + 1);
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(dp[i][j] == inf) continue;
			for(int k = 0; k < 26; ++k) {
				if(nxtS[i][k] != n && nxtT[j][k] == m) {
					ans = min(ans, dp[i][j] + 1);
					break;
				}
			}
		}
	}
	cout << ans << '\n';
	return 0;
}