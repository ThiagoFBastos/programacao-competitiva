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
int low[MAXN], in[MAXN], cc[MAXN], cc_count = 0, scc[MAXN], scc_count = 0, t_in = 0;
stack<int> Q;
void dfs(int v) {
	low[v] = in[v] = t_in++;
	cc[v] = cc_count;
	Q.push(v);
	for(int u : G[v]) {
		if(in[u] == -1) {
			dfs(u);
			low[v] = min(low[v], low[u]);
		}
		else if(scc[u] == -1)
			low[v] = min(low[v], in[u]);
	}
	if(low[v] == in[v]) {
		while(Q.top() != v) {scc[Q.top()] = scc_count; Q.pop();}
		scc[Q.top()] = scc_count++;
		Q.pop();
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for(int k = 0; k < n; ++k)
		in[k] = scc[k] = -1;
	for(int k = 0; k < m; ++k) {
		int u, v;
		cin >> u >> v;
		G[u - 1].push_back(v - 1);
	}
	for(int v = 0; v < n; ++v) {
		if(in[v] == -1) {
			dfs(v);
			++cc_count;
		}
	}
	if(scc_count == 1) cout << "YES\n";
	else {
		cout << "NO\n";
		for(int v = 1; v < n; ++v) {
			if(scc[v] != scc[0]) {
				if(cc[0] != cc[v]) {
					cout << 1 << ' ' << v + 1 << '\n';
					break;
				}
				else {
					cout << v + 1 << ' ' << 1 << '\n';
					break;
				}
			}
		}
	}
	return 0;
} 
