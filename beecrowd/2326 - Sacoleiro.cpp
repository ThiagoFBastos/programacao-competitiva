#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

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
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;


int n, t, p[30], tipo[30], low[30], tempo[30], scc[30], t_in = 0, t_scc = 0, dp[100][201];
bool E[30][30], vis[30];
stack<int> S;
vi G[30], dag[30];

void dfs1(int v) {
	low[v] = tempo[v] = t_in++;
	S.push(v);
	for(int u : G[v]) {
		if(low[u] == -1) {
			dfs1(u);
			low[v] = min(low[u], low[v]);
		} else if(scc[u] == -1)
			low[v] = min(low[v], tempo[u]);
	}
	if(tempo[v] == low[v]) {
		while(S.top() != v) {
			scc[S.top()] = t_scc;
			S.pop();
		}
		scc[S.top()] = t_scc++;
		S.pop();
	}
}

void dfs2(int v) {

	vis[v] = true;

	for(int u : dag[v]) {

		if(!vis[u])
			dfs2(u);

		for(int k = -t; k <= t; ++k)
			dp[v][k + t] = min(dp[v][k + t], dp[u][k + t]);
	}

	for(int u = 0; u < n; ++u) {
		if(scc[u] != v)
			continue;
		else if(tipo[u]) {
			dp[v][p[u] + t] = min(dp[v][p[u] + t], p[u]);
			for(int k = -t; p[u] + k <= t; ++k)
				dp[v][t + k + p[u]] = min(dp[v][t + k + p[u]], dp[v][t + k] + p[u]);
		} else {
			dp[v][t - p[u]] = min(dp[v][t - p[u]], p[u]);
			for(int k = t; k - p[u] >= -t; --k)
				dp[v][t + k - p[u]] = min(dp[v][t + k - p[u]], dp[v][t + k] + p[u]);
		}
	}
}

int solve() {

	for(int k = 0; k < n; ++k) {
		scc[k] = low[k] = -1;
		for(int i = 0; i < n; ++i)
			E[k][i] = false;
	}

	dfs1(0);

	for(int i = 0; i < n; ++i) {
		if(low[i] == -1) continue;
		for(int u : G[i]) {
			if(scc[u] == scc[i]) continue;
			else if(!E[scc[i]][scc[u]]) {
				dag[scc[i]].push_back(scc[u]);
				E[scc[i]][scc[u]] = true;
			}
		}
	}

	for(int k = 0; k < t_scc; ++k) {
		vis[k] = false;
		for(int i = 0; i <= 200; ++i)
			dp[k][i] = 200;
	}

	dfs2(scc[0]);

	int res = 200;

	for(int k = -t; k <= t; ++k)
		if(dp[scc[0]][k + t] <= t)
			res = min(res, abs(k));

	return res;
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> t;

	for(int i = 0; i < n; ++i) {
		int x, r;
		char a;
		cin >> x;
		cin >> p[x] >> a >> r;
		tipo[x] = a - 'A';
		for(int k = 0; k < r; ++k) {
			int y;
			cin >> y;
			G[x].push_back(y);
		}
	}

	cout << solve() << '\n';
	
	return 0;
}