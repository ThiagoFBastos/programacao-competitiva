#include "bits/stdc++.h"
using namespace std;
int r[100], c[100], n, m;
vector<vector<int>> g;
void flow() {
	vector<vector<int>> r(m), f(m);
	vector<int> p(m);
	int ans = 0;
	for(int i = 0; i < m; ++i) {
		r[i].resize(m);
		f[i].assign(m, 0);
	}
	while(true) {
		for(int i = 0; i < m; ++i) for(int j = 0; j < m; ++j) r[i][j] = 0;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < m; ++j) {
				if(g[i][j] > f[i][j]) r[i][j] = g[i][j] - f[i][j];
				if(f[i][j]) r[j][i] = f[i][j];
			}
		}
		queue<int> q;
		fill(p.begin(), p.end(), -1);
		p[0] = 0;
		q.push(0);
		while(!q.empty()) {
			int u = q.front();
			if(u == m - 1) break;
			q.pop();
			for(int v = 0; v < m; ++v) {
				if(p[v] != -1 || !r[u][v]) continue;
				p[v] = u;
				q.push(v);
			}
		}
		if(p[m - 1] == -1) break;
		int c = INT_MAX;
		for(int v = m - 1; v != p[v]; v = p[v]) c = min(c, r[p[v]][v]);
		ans += c;
		for(int v = m - 1; v != p[v]; v = p[v]) {
			int u = p[v];
			if(g[u][v] > f[u][v]) f[u][v] += c;
			else f[v][u] -= c;
		}
	}
	for(int j = 0; j < n; ++j) ans -= c[j];
	if(ans) {
		cout << "-1\n";
		return;
	}
	queue<int> q;
	vector<string> g(n);
	for(int i = 0; i < n; ++i) g[i] = string(n, '.');
	for(int i = 1; i <= n; ++i) for(int j = n + 1; j <= 2 * n; ++j) if(!r[i][j]) g[i - 1][j - n - 1] = 'X';
	for(string& s : g) cout << s << '\n';
}
void solve() {
	cin >> n;
	int L = 0, R = 0;
	for(int i = 0; i < n; L += r[i], ++i) cin >> r[i];
	for(int i = 0; i < n; R += c[i], ++i) cin >> c[i];
	if(L != R) {
		cout << "-1\n";
		return;
	}
	m = 2 * n + 2;
	g = vector<vector<int>>(m, vector<int>(m, 0));
	for(int i = 1; i <= n; ++i) {
		g[0][i] = r[i - 1];
		for(int j = n + 1; j <= 2 * n; ++j) g[i][j] = 1;
	}
	for(int i = n + 1; i <= 2 * n; ++i) g[i][m - 1] = c[i - n - 1];
	flow();
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
