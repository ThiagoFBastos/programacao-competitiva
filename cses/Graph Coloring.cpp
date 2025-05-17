#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 16, INF = 1e9;
 
bool iset[1 << N], adj[N][N];
int dp[1 << N], par[1 << N];
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, m;
 
	cin >> n >> m;
 
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a][b] = adj[b][a] = true;
	}
 
	for(int i = 0; i < (1 << n); ++i) {
		vector<int> v;
 
		for(int j = 0; j < n; ++j) {
			if((i >> j) & 1)
				v.push_back(j);
		}
 
		iset[i] = true;
 
		for(int a : v)
			for(int b : v)
				iset[i] = iset[i] && !adj[a][b];
	}
 
	dp[0] = 0;
 
	for(int i = 1; i < (1 << n); ++i) {
		dp[i] = INF;
		par[i] = -1;
 
		for(int S = i; S; S = (S - 1) & i) {
			if(iset[S]) {
				int colors = 1 + dp[i ^ S];
 
				if(dp[i] > colors) {
					dp[i] = colors;
					par[i] = S;
				}
			}
		}
	}
 
	int colors = dp[(1 << n) - 1];
	int S = (1 << n) - 1;
 
	cout << colors << '\n';
 
	vector<int> c(n, -1);
 
	for(int i = 1; i <= colors; ++i) {
		for(int j = 0; j < n; ++j) {
			if(par[S] & (1 << j))
				c[j] = i;
		}
		S ^= par[S];
	}
 
	for(int v : c) cout << v << ' ';
	cout << '\n';
 
	return 0;
}
