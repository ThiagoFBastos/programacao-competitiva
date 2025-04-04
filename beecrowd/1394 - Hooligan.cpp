#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2,sse3")
#include "bits/stdc++.h"
using namespace std;
const int N = 40;
int n, c[N][N], p[N];
int flow(vector<vector<int>>& C) {
	int m = C.size(), fluxo = 0;
	vector<vector<int>> F(m, vector<int>(m, 0)), R(m, vector<int>(m, 0)), G(m);
	vector<int> pai(m);
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < m; ++j) {
			if(C[i][j]) {
				G[i].push_back(j);
				G[j].push_back(i);
				R[i][j] = C[i][j];
			}
		}
	}
	while(true) {
		queue<int> q;
		fill(pai.begin(), pai.end(), -1);
		pai[0] = 0;
		q.push(0);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			if(u == m - 1) break;
			for(int v : G[u]) {
				if(!R[u][v] || pai[v] != -1) continue;
				pai[v] = u;
				q.push(v);
			}
		}
		if(pai.back() == -1) break;
		int x {INT_MAX};
		for(int u = m - 1; u; u = pai[u]) {
			x = min(x, R[pai[u]][u]);
			R[pai[u]][u] = R[u][pai[u]] = 0;
		}
		for(int u = m - 1; u; u = pai[u]) {
			int v = pai[u];
			if(C[v][u] - F[v][u]) {
				F[v][u] += x;
				if(C[v][u] - F[v][u]) R[v][u] = C[v][u] - F[v][u];
				R[u][v] = F[v][u];
			} else {
				F[u][v] -= x;
				if(C[u][v] - F[u][v]) R[u][v] = C[u][v] - F[u][v];
				if(F[u][v]) R[v][u] = F[u][v];
			}
		}
		fluxo += x;
	}
	return fluxo;
}
bool solve() {
	int K = n * (n - 1) / 2 + n + 2;
	vector<vector<int>> C(K, vector<int>(K, 0));
	int P = p[0], R = 0;
	for(int j = 0; j < n; ++j) P += 2 * c[0][j];
	for(int j = 1; j < n; ++j) if(P <= p[j]) return false;
	for(int i = 1, k = 1; i <= n; ++i) {
		for(int j = i + 1; j <= n; ++k, ++j) {
			R += c[i - 1][j - 1];
			C[0][k] = C[k][n * (n - 1) / 2 + i] = C[k][n * (n - 1) / 2 + j] = 2 * c[i - 1][j - 1];
		}
	}
	C[n * (n - 1) / 2 + 1][K - 1] = P - p[0];
	for(int i = 2; i <= n; ++i) C[n * (n - 1) / 2 + i][K - 1] = P - 1 - p[i - 1];
	return flow(C) == 2 * R;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true) {
		int k, m;
		cin >> n >> m >> k;
		if(!n) break;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				c[i][j] = i == j ? 0 : m;
		memset(p, 0, n * sizeof(int));
		while(k--) {
			int a, b;
			char _;
			cin >> a >> _ >> b;
			--c[a][b], --c[b][a];
			if(_ == '=') ++p[a], ++p[b];
			else if(_ == '<') p[b] += 2;
			else p[a] += 2;
		}
		cout << (solve() ? "Y\n" : "N\n");
	}
	return 0;
}