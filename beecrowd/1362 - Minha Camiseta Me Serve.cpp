#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
const int MAXP = 36, MAXQ = 30;
bool G[MAXP + MAXQ][MAXP + MAXQ];
int n, m;
int matching() {
	n *= 6;
	bool M[MAXP + MAXQ][MAXP + MAXQ], f[MAXP + MAXQ];
	int p[MAXP + MAXQ][2], N = m + n;
	for(int u = N - 1; u >= 0; --u) {
		f[u] = true;
		for(int v = N - 1; v >= 0; --v)
			M[u][v] = false;
	}
	while(true) {
		queue<pair<int, int>> S;	
		for(int u = N - 1; u >= 0; --u) {
			p[u][0] = p[u][1] = -1;
			if(f[u]) {
				p[u][0] = u;
				S.push({u, 0});
			}
		}
		int v = -1;
		while(!S.empty()) {
			auto [u, t] = S.front();
			S.pop();
			if(t) {
				if(f[u]) {
					v = u;
					break;
				}
				for(int w = N - 1; w >= 0; --w) {
					if(G[u][w] && p[w][0] == -1 && M[u][w]) {
						p[w][0] = u;
						S.push({w, 0});
					}
				}
			}
			else {
				for(int w = N - 1; w >= 0; --w) {
					if(G[u][w] && p[w][1] == -1 && !M[u][w]) {
						p[w][1] = u;
						S.push({w, 1});
					}
				}
			}
		}
		if(v == -1) break;
		for(int e = 1; ; e ^= 1) {
			int u = p[v][e];
			f[v] = false;
			if(u == v) break;
			else if(e) M[u][v] = M[v][u] = true;
			else M[u][v] = M[v][u] = false;
			v = u;
		}
	}
	int emp = 0;
	for(int u = 0; u < m; ++u)
		for(int v = N - 1; v >= m; --v)
			if(M[u][v]) ++emp;
	return emp;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	string cam[] = {"L", "XL", "M", "S", "XS", "XXL"};
	cin >> T;
	while(T--) {
		cin >> n >> m;
		for(int u = n + m - 1; u >= 0; --u)
			for(int v = n + m - 1; v >= 0; --v)
				G[u][v] = false;
		n /= 6;
		for(int k = 0; k < m; ++k) {
			string c1, c2;
			cin >> c1 >> c2;
			int u, v;
			u = find(cam, cam + 6, c1) - cam;
			v = find(cam, cam + 6, c2) - cam;
			for(int a = 0; a < n; ++a)
				G[m + n * u + a][k] = G[m + n * v + a][k] = G[k][m + n * u + a] = G[k][m + n * v + a] = true;
		}
		if(matching() == m) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}