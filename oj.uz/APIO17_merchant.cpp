#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;	
 
const int N = 100, M = 1000;
 
i64 tms[N][N], cost[N][N], d[N][N];
int buy[N][M], sell[N][M];
int n, m, k;
 
void solve() {
	cin >> n >> m >> k;
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) tms[i][j] = i == j ? 0 : INFLL;
		for(int j = 0; j < k; ++j) cin >> buy[i][j] >> sell[i][j];
	}
 
	for(int i = 0; i < m; ++i) {
		int u, v, t;
		cin >> u >> v >> t;	
		--u, --v;
		tms[u][v] = t;
	}
 
	for(int k = 0; k < n; ++k)
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		tms[i][j] = min(tms[i][j], tms[i][k] + tms[k][j]);
	
	int l = 0, r = 1e9 + 1;
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			for(int l = 0; l < k; ++l) {
				i64 X = min(sell[j][l], buy[i][l]) >= 0 ? max(0, sell[j][l] - buy[i][l]) : 0;
				d[i][j] = max(X, d[i][j]);				
			}
		}
	}
 
	while(l < r) {
		int m = (l + r) / 2;
 
		for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			cost[i][j] = i != j && tms[i][j] != INFLL ? d[i][j] - m * tms[i][j] : -INFLL;
 
		for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			cost[i][j] = max(cost[i][j], cost[i][k] + cost[k][j]);
 
		bool ok = false;
 
		for(int i = 0; i < n; ++i) ok = ok || cost[i][i] >= 0;
 
		if(!ok) r = m;
		else l = m + 1;
	}
 
	cout << max(0, r - 1) << '\n';
}	
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
