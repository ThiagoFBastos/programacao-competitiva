#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int N = 300;
const i64 linf = 1e15L;

i64 dist[N][N];
int d[N][N];

void solve() {
	int n, m, l;
	queue<int> qu;

	cin >> n >> m >> l;

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			dist[i][j] = i == j ? 0 : linf;
			d[i][j] = -1;
		}
	}
	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		dist[a][b] = dist[b][a] = c;
	}
	
	for(int k = 0; k < n; ++k)
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

	int q;

	cin >> q;

	while(q--) {
		int s, t;
		cin >> s >> t;
		--s, --t;

		if(d[s][s] == -1) {
			d[s][s] = 0;
			qu.push(s);
			while(!qu.empty()) {
				int u = qu.front();
				qu.pop();
				for(int v = 0; v < n; ++v) {
					if(dist[u][v] > l || d[s][v] != -1) continue;
					d[s][v] = 1 + d[s][u];
					qu.push(v);
				}
			}
		}
		
		if(d[s][t] < 0) cout << "-1\n";
		else cout << d[s][t] - 1 << '\n';
	}

}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
