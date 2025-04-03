#pragma GCC optimize("O3")
#pragma GCC target("mmx", "sse", "sse2", "sse3", "sse4", "avx")
#include <bits/stdc++.h>

using namespace std;

using ii = pair<int, int>;

#define X first
#define Y second

vector<vector<int>> g;
vector<vector<ii>> p;
vector<vector<double>> dp;
int n;

void dfs(int u, int pai) {
	for(int v : g[u]) {
		if(v == pai) continue;
		dfs(v, u);
		for(int k = 0; k < (int)size(p[u]); ++k) {
			double dist = INT_MAX;
			for(int j = 0; j < (int)size(p[v]); ++j)
				dist = min(dist, dp[v][j] + hypot(0.0 + p[u][k].X - p[v][j].X, 0.0 + p[u][k].Y - p[v][j].Y));
			dp[u][k] += dist;
		}
	}
}

void solve() {
	cin >> n;
	if(!n) exit(0);
	
	map<string, int> dict;
	
	g = vector<vector<int>>(n);
	p = vector<vector<ii>>(n);
	dp = vector<vector<double>>(n);
	
	for(int i = 0; i < n; ++i) {
		string c;
		int m;
		cin >> c >> m;
		dict[c] = i;
		p[i].resize(m);
		dp[i].assign(m, 0);
		for(int j = 0; j < m; ++j) cin >> p[i][j].X >> p[i][j].Y;
	}
	
	for(int i = 1; i < n; ++i) {
		string a, b;
		cin >> a >> b;
		int u = dict[a];
		int v = dict[b];
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	dfs(0, -1);
	
	cout << *min_element(dp[0].begin(), dp[0].end()) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.setf(ios_base :: fixed);
	cout.precision(1);
	int t = 1;
	//cin >> t;
	while(true) solve();
	return 0;
}