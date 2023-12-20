#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100000
vi G[MAXN];
int dp[MAXN];
void dfs(int v) {
	int longest_path = 0;
	dp[v] = 0;
	for(int w : G[v]) {
		if(dp[w] == -1)
			dfs(w);
		longest_path = max(longest_path, dp[w]);
	}
	if(longest_path) dp[v] = 1 + longest_path;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	memset(dp, -1, n * sizeof(int));
	for(int i = 0; i < m; ++i) {
		int s, t;
		cin >> s >> t;
		G[s - 1].push_back(t - 1);
	}
	dp[n - 1] = 1;
	dfs(0);
	if(dp[0]) {
		cout << dp[0] << '\n';
		int path = dp[0], v = 0;
		while(true) {
			cout << v + 1 << ' ';
			if(v == n - 1) break;
			for(int w : G[v]) {
				if(dp[w] == dp[v] - 1) {
					--path;
					v = w;
					break;
				}
			}
		}
		cout << '\n';
	}
	else cout << "IMPOSSIBLE\n";
	return 0;
}
