#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
#define MAXN 200000
vi G[MAXN];
int n, h[MAXN], max_h[MAXN], max_dist[MAXN];
void dfs1(int v, int level) {
	max_h[v] = h[v] = level;
	for(int u : G[v]) {
		if(h[u] == -1) {
			dfs1(u, level + 1);
			max_h[v] = max(max_h[v], max_h[u]);
		}
	}
}
void dfs2(int v, int l) {
	max_dist[v] = max(max_h[v] - h[v], h[v] + l);
	int x = 0, y = 0;
	for(int u : G[v]) {
		if(h[u] == 1 + h[v]) {
			if(x < max_h[u]) {
				y = x;
				x = max_h[u];		
			}
			else if(y < max_h[u])
				y = max_h[u];
		}
	}
	for(int u : G[v]) {
		if(max_dist[u] == -1) {
			int k;
			if(x == max_h[u]) k = y;
			else k = x;
			dfs2(u, max(k - 2 * h[v], l));
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int k = 1; k < n; ++k) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int k = 0; k < n; ++k)
		h[k] = max_dist[k] = -1;
	dfs1(0, 0);
	dfs2(0, 0);
	for(int k = 0; k < n; ++k)
		cout << max_dist[k] << ' ';
	cout << '\n';
    return 0;
}
 
