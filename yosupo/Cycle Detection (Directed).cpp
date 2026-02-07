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

const int N = 5e5 + 10;

int n, m, low[N], t[N], scc[N], tms;
vector<ii> adj[N];
vector<int> cycle;
stack<int> st;

void dfs(int v) {
	low[v] = t[v] = tms++;
	st.push(v);
	for(auto [u, e] : adj[v]){
		if(t[u] == -1){
			dfs(u);
			low[v] = min(low[v], low[u]);
		} else if(scc[u] == -1) low[v] = min(low[v], t[u]);
	}
	if(t[v] == low[v]){
		while(st.top() != v){
			scc[st.top()] = tms;
			st.pop();
		}	
		scc[st.top()] = tms++;
		st.pop();
	}
}

void solve() {
	cin >> n >> m;	
	memset(t, -1, sizeof t);
	memset(scc, -1, sizeof scc);
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		adj[a].emplace_back(b, i);
	}
	for(int v = 0; v < n; ++v) {
		if(t[v] < 0) dfs(v);
		for(auto [u, e] : adj[v]) {
			if(scc[u] != scc[v]) continue;
			queue<int> q;
			vector<int> p(n, -1), cycle;	
			p[u] = u; q.push(u);
			while(!q.empty()) {
				int u = q.front();
				q.pop();
				if(u == v) break;
				for(auto [v, e] : adj[u]) {
					if(p[v] >= 0) continue;
					p[v] = u; q.push(v);
				}
			}
			while(true) {
				cycle.push_back(v);
				if(v == u) break;
				v = p[v];
			}		
			reverse(cycle.begin(), cycle.end());
			int L = cycle.size();
			cout << L << '\n';
			for(int i = 0; i < L; ++i) {
				int u = cycle[i];
				for(auto [v, e] : adj[u]) {
					if(cycle[(i+1)%L] == v) {
						cout << e << '\n';
						break;
					}
				}
			}
			return;
		}
	}
	cout << "-1\n";
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}