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
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, dist[MAXN], p[MAXN];
	vi G[MAXN];
	queue<int> Q;
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u; --v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	memset(dist, -1, n * sizeof(int));
	Q.push(n - 1);
	dist[n - 1] = 1;
	while(!Q.empty()) {
		int t = Q.front();
		if(t == 0) break;
		Q.pop();
		for(int v : G[t]) {
			if(dist[v] == -1) {
				p[v] = t;
				dist[v] = 1 + dist[t];
				Q.push(v);
			}
		}
	}
	if(dist[0] == -1) cout << "IMPOSSIBLE\n";
	else {
		int t = 0;
		cout << dist[0] << '\n';
		while(t != n - 1) {
			cout << t + 1 << ' ';
			t = p[t];
		}
		cout << n << '\n';
	}	
    return 0;
}
