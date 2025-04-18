#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e3 + 10;

int n, m, low[N], in[N], scc[N], tms, cnt_scc;
vector<int> adj[N], st;

void dfs(int u) {
	low[u] = in[u] = tms++;
	st.push_back(u);
	for(int v : adj[u]) {
		if(in[v] == -1) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if(scc[v] == -1)
			low[u] = min(low[u], low[v]);
	}
	if(low[u] != in[u]) return;
	while(st.back() != u) {
		scc[st.back()] = cnt_scc;
		st.pop_back();
	}
	st[st.back()] = cnt_scc++;
	st.pop_back();
}

void solve() {
	
	while(true) {
		cin >> n >> m;

		if(!n && !m) break;

		for(int i = 0; i < n; ++i) adj[i].clear();

		for(int i = 0; i < m; ++i) {
			int v, w, p;
			cin >> v >> w >> p;
			--v, --w;
			if(p == 1) adj[v].pb(w);
			else {
				adj[v].pb(w);
				adj[w].pb(v);
			}
		}

		memset(in, -1, n * sizeof(int));
		memset(scc, -1, n * sizeof(int));
		tms = cnt_scc = 0;

		dfs(0);

		if(tms != n || cnt_scc > 1)
			cout << "0\n";
		else
			cout << "1\n";
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
