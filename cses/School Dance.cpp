#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
const int MAXN = 1000;
int n, m, k;
vi G[MAXN];
void matching() {
	bool f[MAXN];
	int p[MAXN][2], M[MAXN][MAXN], N = n + m;
	for(int u = 0; u < N; ++u) {
		p[u][0] = p[u][1] = -1;
		f[u] = true;
		for(int v = 0; v < N; ++v)
			M[u][v] = 0;
	}
	while(true) {
		int u = -1;
		queue<pair<int, int>> S;
		for(int v = 0; v < N; ++v) {
			p[v][0] = p[v][1] = -1;
			if(f[v]) {
				p[v][0] = v;
				S.push({v, 0});
			}
		}
		while(!S.empty()) {
			auto [v, t] = S.front();
			S.pop();
			if(t && f[v]) {
				u = v;
				break;
			}
			for(int w : G[v]) {
				if(p[w][t ^ 1] == -1 && M[v][w] == t) {
					p[w][t ^ 1] = v;
					S.push({w, t ^ 1});
				}
			}
		}
		if(u == -1) break;
		for(int i = 1; ; i ^= 1) {
			int v = p[u][i];
			f[u] = false;
			if(v == u) break;
			M[u][v] = M[v][u] = i;
			u = v;
		}
	}
	int mat = 0;
	for(int u = 0; u < m; ++u)
		for(int v = m; v < N; ++v)
			mat += M[u][v];
	cout << mat << '\n';
	for(int u = 0; u < m; ++u) {
		for(int v = m; v < N; ++v) {
			if(M[u][v]) {
				cout << v - m + 1 << ' ' << u + 1 << '\n';
				break;
			}
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 0; i < k; ++i) {
		int b, g;
		cin >> b >> g;
		--g, --b;
		G[g].push_back(b + m);
		G[b + m].push_back(g);
	}
	matching();
	return 0;
}
