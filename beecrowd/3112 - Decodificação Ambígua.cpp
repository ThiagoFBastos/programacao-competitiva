#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree <int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
using namespace std;
using namespace __gnu_pbds;
const int MAXN = 2e4 + 1;
int n, m;
unordered_map<char, string> t;
unordered_set<string> dic;
string msg, cod;
int decod[MAXN][20];
long long dp[MAXN];
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	dic.reserve(n);
	for(int i = 0; i < n; ++i) {
		string s;
		char c;
		cin >> s >> c;
		t[c] = s;
		dic.insert(s);
	}
	cin >> msg;
	for(char ch : msg) 
		cod += t[ch];
	char K[MAXN];
	strcpy(K, cod.c_str());
	m = cod.size();
	for(int i = 0; i < m; ++i) {
		dp[i] = 0;
		for(int k = 0; k < 20; ++k)
			decod[i][k] = 0;
	}
	for(int L = 1; L <= 20; ++L) {
		for(int k = 0; k <= m - L; ++k) {
			char ch = K[k + L];
			K[k + L] = '\0';
			decod[k][L - 1] = dic.count(K + k);
			K[k + L] = ch;
		}
	}
	for(int i = max(0, m - 20); i < m; ++i)
		dp[i] = decod[i][m - i - 1];
	for(int k = m - 1; k >= 0; --k) {
		for(int i = k + 1; i < m && i - k < 20; ++i) {
			dp[k] += dp[i] * decod[k][i - k - 1];
			if(dp[k] >= 2) dp[k] = 2;
		}
	}
	if(dp[0] > 1) cout << "Yes\n";
	else cout << "No\n";
	return 0;
}