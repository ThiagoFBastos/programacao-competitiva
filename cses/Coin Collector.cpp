#include <bits/stdc++.h>
 
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
 
using namespace std;
 
typedef long long ll;
 
using vi = vector<int>;
using ii = pair<int, int>;
 
vector<vi> G, Gscc;
vi scc, pre, low, coins;
vector<ll> dp, scc_coins;
stack<int> Q;
int timestamp, sc, n, m;;
 
void dfs(int v) {
 
	pre[v] = low[v] = ++timestamp;	
	Q.push(v);
 
	for(int u : G[v]) {
 
		if(pre[u] == -1) {
 
			dfs(u);
			low[v] = min(low[v], low[u]);
		}
 
		else if(scc[u] == -1)
			low[v] = min(low[v], pre[u]);		
	}
 
	if(pre[v] == low[v]) {
 
		scc[v] = sc;
 
		while(Q.top() != v) {
 
			scc[Q.top()] = sc;
			Q.pop();
		}
	
		++sc;
		Q.pop();		
	}
}
 
 
void max_dfs(int v) {
 
	ll ans {};
 
	dp[v] = scc_coins[v];
 
	for(int u : Gscc[v]) {
 
		if(dp[u] == -1) max_dfs(u);
		ans = max(ans, dp[u]);
	}	
 
	dp[v] += ans;
}
 
ll solve() {
 
	pre.resize(n);
	low.resize(n);
	scc.resize(n);
	timestamp = sc = 0;
 
	for(int v = 0; v < n; ++v)
		scc[v] = pre[v] = -1;
		
	for(int v = 0; v < n; ++v) {
 
		if(pre[v] == -1)
			dfs(v);
	}
 
	scc_coins.assign(++sc, 0);
	Gscc.resize(sc);
	dp.assign(sc, -1);
 
	for(int v = 0; v < n; ++v) {
 
		scc_coins[scc[v]] += coins[v];
 
		for(int u : G[v]) {
 
			if(scc[v] != scc[u])
				Gscc[scc[v]].push_back(scc[u]);
		}
	}
 
	for(int v = 0; v < sc; ++v) {
 
		if(dp[v] == -1)
			max_dfs(v);
	}
 
	return 	*max_element(dp.begin(), dp.end());
}
 
 
int main() {
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
 
	cin >> n >> m;
 
	coins.resize(n);
 
	for(int k = 0; k < n; ++k)
		cin >> coins[k];
 
	G.resize(n);
 
	for(int k = 1; k <= m; ++k) {
 
		int u, v;
 
		cin >> u >> v;
 
		G[u - 1].push_back(v - 1);
	}
 
	cout << solve() << '\n';
	
	return 0;
}
