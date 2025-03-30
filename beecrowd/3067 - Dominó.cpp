#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

int d[7], vis;
bool g[7][7], seen[7];

void dfs(int v) {
	seen[v] = true;
	++vis;
	for(int u = 0; u < 7; ++u) {
		if(g[v][u] && !seen[u])
			dfs(u);
	}
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t = 0;

	while(true) {
		int n, odd = 0, non_zero = 0;
		cin >> n;
		if(n == 0)
			break;

		memset(&g[0][0], 0, sizeof g);
		memset(d, 0, sizeof d);
		memset(seen, 0, sizeof seen);

		for(int i = 0; i < n; ++i) {
			int x, y;
			cin >> x >> y;
			g[x][y] = g[y][x] = true;
			++d[x];
			++d[y];
		}

		vis = 0;

		for(int i = 0; i < 7; ++i) {
			if(d[i]) {
				dfs(i);
				break;
			}
		}

		for(int i = 0; i < 7; ++i) {
			if(d[i] & 1) ++odd;
			if(d[i]) ++non_zero;
		}

		cout << "Teste " << ++t << '\n' << (vis == non_zero && (odd == 0 || odd == 2) ? "sim\n" : "nao\n") << '\n';
	}

	return 0;
}