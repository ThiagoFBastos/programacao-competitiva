#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e5 + 100;

int n, m, low[N], t[N], scc[N], scc_cnt[N], tms, id, type[N];

vector<int> st;
vector<int> adj[N];

void dfs(int u) {
	low[u] = t[u] = tms++;
	st.push_back(u);
	for(int v : adj[u]) {
		if(low[v] == -1) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if(scc[v] == -1) low[u] = min(low[u], low[v]);
	}
	if(low[u] == t[u]) {
		while(true) {
			int v = st.back();
			st.pop_back();
			scc[v] = id;
			++scc_cnt[id];
			if(u == v) break;
		}
		++id;
	}
}


void get(int u) {
	type[u] = 0;
	for(int v : adj[u]) {
		if(type[v] < 0) get(v);
		type[u] |= type[v];
	}
}

void solve() {

	memset(low, -1, sizeof low);
	memset(scc, -1, sizeof scc);
	memset(type, -1, sizeof type);

	cin >> n >> m;

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
	}
	
	for(int i = 0; i < n; ++i) if(low[i] < 0) dfs(i);

	for(int i = 0; i < n; ++i) if(scc_cnt[scc[i]] > 1) type[i] = 1;
	
	for(int i = 0; i < n; ++i) if(type[i] < 0) get(i);

	cout << count(type, type + n, 1) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
