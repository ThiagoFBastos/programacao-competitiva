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
int p[MAXN];
bool dfs(int v) {
	for(int u : G[v]) {
		if(p[u] == 0) {
			p[u] = -p[v];
			if(!dfs(u)) return false;
		}
		else if(p[u] == p[v])
			return false;
	}
	return true;
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
	memset(p, 0, n * sizeof(int));
	bool b {true};
	for(int v = 0; v < n; ++v) {
		if(!p[v]) {
			p[v] = 1;
			if(!dfs(v)) {
				b = false;
				break;
			}
		}
	}
	if(b) {
		for(int v = 0; v < n; ++v) if(p[v] == -1) cout << 1 << ' '; else cout << 2 << ' ';
		cout << '\n';
	}
	else
		cout << "IMPOSSIBLE\n";
    return 0;
}
