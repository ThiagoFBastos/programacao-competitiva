#pragma GCC optimize("O3,unroll-loops")

#include "bits/stdc++.h"

using namespace std;

const int N = 200, inf = 1e9;

int tim[26][26], dp[N][N][26];
char type[26][26];
vector<pair<int, int>> g[26];

void solve() {
	int n, q;
	
	cin >> n;
	
	if(!n) exit(0);
	
	vector<char> alpha(n);
	vector<int> p(26);
	
	for(int i = 0; i < n; ++i) {
		g[i].clear();
		cin >> alpha[i];
		p[alpha[i] - 'a'] = i;
	}
	
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			string str;
			cin >> str;
			sscanf(str.c_str(), "%d-%c", &tim[i][j], &type[i][j]);
			int k = p[type[i][j] - 'a'];
			g[k].emplace_back(i, j);
		}
	}
	
	cin >> q;
	
	while(q--) {
		string str;
		
		cin >> str;
		
		int m = str.size();
		
		for(int i = 0; i < m; ++i)
		for(int j = 0; j < m; ++j)
		for(int k = 0; k < n; ++k)
			dp[i][j][k] = inf;
			
		for(int i = 0; i < m; ++i) dp[i][i][p[str[i] - 'a']] = 0;
		
		for(int i = 2; i <= m; ++i) {
			for(int L = 0; L + i <= m; ++L) {
				int R = L + i - 1;		
				for(int i = 0; i < n; ++i) {
					int ans = inf;
					for(auto [x, y] : g[i])
					for(int k = L; k < R; ++k) ans = min(ans, dp[L][k][x] + dp[k + 1][R][y] + tim[x][y]);
					dp[L][R][i] = ans;
				}
			}
		}
	
		auto ans = make_pair(inf, inf);
		for(int i = 0; i < n; ++i) ans = min(ans, make_pair(dp[0][m - 1][i], i));
		cout << ans.first << '-' << alpha[ans.second] << '\n';
	}
	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}