#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9;

vector<vector<int>> g;
vector<int> low, t, scc;
int tms, scc_tms, n, m;
stack<int> st;

void dfs(int u) {
	low[u] = t[u] = tms++;
	st.push(u);
	
	for(int v : g[u]) {
		if(t[v] == -1) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if(scc[v] == -1) low[u] = min(low[u], t[v]);
	}
	
	if(low[u] == t[u]) {
		
		while(true) {
			int v = st.top();
			st.pop();
			scc[v] = scc_tms;
			if(v == u) break;
		}
		
		++scc_tms;
	}
}

vector<vector<int>> G;
vector<int> cnt, dp, estado;
vector<bool> controle;

int mod_sum(int x) {
	return x >= mod ? x - mod : x;
}

bool dag(int u) {
	if(u == scc[1]) estado[u] = dp[u] = 1;
	else {
		for(int v : G[u]) {
			if(estado[v] == -1 && !dag(v)) return false;
			if(estado[v] == 1) estado[u] = 1;
			controle[u] = controle[u] || controle[v] || dp[u] + dp[v] >= mod;
			dp[u] = mod_sum(dp[u] + dp[v]);
		}	
		if(estado[u] == -1) estado[u] = 0;
	}
	return !estado[u] || estado[u] == 1 && cnt[u] == 1;
}


void solve() {

	cin >> n >> m;
	
	g.resize(n);
	low.resize(n);
	t.assign(n, -1);
	scc.assign(n, -1);
	
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		g[a - 1].push_back(b - 1);
	}	
	
	for(int v = 0; v < n; ++v) if(t[v] == -1) dfs(v);
	
	G.resize(scc_tms);
	cnt.assign(scc_tms, 0);
	controle.assign(scc_tms, false);
	estado.assign(scc_tms, -1);
	dp.assign(scc_tms, 0);
	
	for(int v = 0; v < n; ++v) {
		++cnt[scc[v]];
		for(int u : g[v]) if(scc[v] != scc[u]) G[scc[v]].push_back(scc[u]);
	}
	
	int v = scc[0];
	
	if(dag(v)) {
		if(controle[v]) {
			cout.width(9);
			cout.fill('0');
		}
		cout << dp[v] << '\n';
	} else cout << "inf\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}