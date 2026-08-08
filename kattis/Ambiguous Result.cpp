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

const int maxn = 201;
pair<ll, ll> dp[maxn][maxn];

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	while(true) {
		string s;
		cin >> s;
		if(s == "END") break;
		int n = s.size();
		for(int k = 0; k <= n; ++k)
			for(int i = 0; i <= n; ++i)
				dp[k][i] = {LLONG_MAX, -1};
		for(int k = 0; k < n; ++k) {
			if(isdigit(s[k])) {
				int i = k;
				ll K = 0;
				while(i < n && isdigit(s[i])) {
					K = 10 * K + s[i] - '0';
					++i;
				}
				dp[i - k][k] = {K, K};
				k = i - 1;
			}
		}
		for(int i = 3; i <= n; ++i) {
			for(int k = 0; k <= n - i; ++k) {
				if(isdigit(s[k]) && !(k > 0 && isdigit(s[k - 1])) && isdigit(s[k + i - 1]) && !(k + i < n && isdigit(s[k + i]))) {			
					for(int j = k; j < k + i; ++j) {
						if(s[j] == '+') {
							dp[i][k].first = min(dp[i][k].first, dp[j - k][k].first + dp[k + i - j - 1][j + 1].first);
							dp[i][k].second = max(dp[i][k].second, dp[j - k][k].second + dp[k + i - j - 1][j + 1].second);
						} else if(s[j] == '*') {
							dp[i][k].first = min(dp[i][k].first, dp[j - k][k].first * dp[k + i - j - 1][j + 1].first);
							dp[i][k].second = max(dp[i][k].second, dp[j - k][k].second * dp[k + i - j - 1][j + 1].second);
						}
					}
				}
			}
		}
		cout << dp[n][0].first << ' ' << dp[n][0].second << '\n';
	}
    return 0;
}