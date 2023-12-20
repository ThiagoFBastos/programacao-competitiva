#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
#define f first
#define s second
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100000
vi G[MAXN];
int low[MAXN], in[MAXN], scc[MAXN], t_in = 0, scc_id = 0;
stack<int> Q;
void dfs(int v) {
	low[v] = in[v] = t_in++;
	Q.push(v);
	for(int u : G[v]) {
		if(in[u] == -1) {
			dfs(u);
			low[v] = min(low[v], low[u]);
		}
		else if(scc[u] == -1) low[v] = min(low[v], in[u]);
	}
	if(low[v] == in[v]) {
		int u;
		do
		{
			u = Q.top();
			Q.pop();
			scc[u] = scc_id;
		} while(u != v);
 
		scc_id++;
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		G[u - 1].push_back(v - 1);
	}
	for(int v = 0; v < n; ++v)
		in[v] = scc[v] = -1;
	for(int v = 0; v < n; v++) {
		if(in[v] == -1)
			dfs(v);
	}
	cout << scc_id << '\n';
	for(int v = 0; v < n; ++v)
		cout << scc[v] + 1 << ' ';
	cout << '\n';
	return 0;
} 
