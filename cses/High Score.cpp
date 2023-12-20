#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 2500
#define INF 2500000000001LL
vii G[MAXN]; 
vi Gout[MAXN];
ll score[MAXN];
int n, m;
bool maximize() {
	bool r {};
	for(int v = 0; v < n; ++v) {
		if(score[v] != -INF) {
			for(auto [u, du] : G[v]) {
				if(score[v] + du > score[u]) {
					r = true;
					score[u] = du + score[v];
				}
			}
		}
	}
	return r;
}
int cc[MAXN], cc_id = 0;
void dfs(int v) {
	cc[v] = cc_id;
	for(int u : Gout[v]) {
		if(cc[u] == -1)
			dfs(u);
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;	
	for(int v = 0; v < n; ++v)  {
		score[v] = -INF;
		cc[v] = -1;
	}
	for(int k = 0; k < m; ++k) {
		int u, v, c;
		cin >> u >> v >> c;
		G[u - 1].push_back({v - 1, c});
		Gout[v - 1].push_back(u - 1);
	}
	dfs(n - 1);
	score[0] = 0;
	for(int k = 1; k < n && maximize(); ++k);
	bool c_pos = false;
	for(int v = 0; v < n; ++v) {
		if(score[v] != -INF) {
			for(auto [u, du] : G[v]) {
				if(score[v] + du > score[u]) {
					if(cc[u] != -1) {
						c_pos = true;
						v = n;
						break;
					}
					score[u] = du + score[v];
				}
			}
		}
	}
	if(c_pos) cout << -1 << '\n';
	else cout << score[n - 1] << '\n';
	return 0;
}
