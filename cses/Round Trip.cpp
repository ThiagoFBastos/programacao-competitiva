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
#define MAXN 100000
vi G[MAXN];
int in[MAXN], p[MAXN], t_in = 0, v1 = -1, v2 = -1;
void dfs(int v) {
	in[v] = t_in++;
	for(int u : G[v]) {
		if(in[u] == -1) {
			p[u] = v;
			dfs(u);
		}
		else if(u != p[v])
			v1 = u, v2 = v;
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for(int k = 0; k < m; ++k) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	memset(in, -1, n * sizeof(int));
	for(int v = 0; v < n; ++v) {
		if(in[v] == -1) {
			p[v] = v;
			dfs(v);
			if(v1 != -1)
				break;
		}
	}
	if(v1 == -1) cout << "IMPOSSIBLE\n";
	else { 
		vi V;
		if(in[v1] > in[v2]) swap(v1, v2);
		while(v1 != v2) {
			V.push_back(v2);
			v2 = p[v2];
		}
		V.push_back(v2);
		cout << V.size() + 1 << '\n';
		for(int v : V) cout << v + 1 << ' ';
		cout << V.front() + 1 << '\n';
	}
    return 0;
}
