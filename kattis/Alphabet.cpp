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
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s, alpha;
	int dp[51][27];
	cin >> s;
	for(char c = 'a'; c <= 'z'; ++c) alpha += c;
	for(int i = 0; i <= 26; ++i) dp[0][i] = 0;
	for(int i = 0; i <= (int)s.size(); ++i) dp[i][0] = 0;	
	for(int i = 1; i <= (int)s.size(); ++i) {
		for(int k = 1; k <= 26; ++k) {
			dp[i][k] = dp[i - 1][k - 1];
			if(s[i - 1] == alpha[k - 1]) ++dp[i][k];
			dp[i][k] = max({dp[i][k], dp[i - 1][k], dp[i][k - 1]});
		}
	}
	cout << 26 - dp[s.size()][26] << '\n';
	return 0;
}

