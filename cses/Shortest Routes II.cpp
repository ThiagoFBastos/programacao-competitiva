#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 500
#define INF 500000000000LL
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	ll D[MAXN][MAXN];
	cin >> n >> m >> q;
	for(int k = 0; k < n; ++k) {
		for(int i = 0; i < n; ++i)
			D[k][i] = INF;
		D[k][k] = 0;
	}
	for(int k = 0; k < m; ++k) {
		int u, v, c;
		cin >> u >> v >> c;
		--u, --v;
		D[u][v] = D[v][u] = min(D[u][v], 0LL + c);
	}
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
			if(D[k][i] == INF) D[k][i] = -1;
	while(q--) {
		int u, v;
		cin >> u >> v;
		cout << D[u - 1][v - 1] << '\n';		
	}
	return 0;
}
