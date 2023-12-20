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
 
const int N = 8;
 
int moves[N][N], tms[N][N], xi, yi;
vector<ii> adj[N][N], to[N][N][9];
ii delta[] = {
	{1, 2},
	{1, -2},
	{-1, 2},
	{-1, -2},
	{2, 1},
	{-2, 1},
	{2, -1},
	{-2, -1}
};
 
bool backtrack(int x, int y, int t) {
	tms[x][y] = t;
 
	if(t == 64) return true;
	
	for(int i = 0; i <= 8; ++i) to[x][y][i].clear();
 
	for(auto [i, j] : adj[x][y]) {
		--moves[i][j];
		if(tms[i][j] == -1) to[x][y][moves[i][j]].pb({i, j});
	}
 
	for(int k = 0; k <= 8; ++k) {
		auto& A = to[x][y][k];
		if(A.empty()) continue;
		for(auto [i, j] : A)
			if(backtrack(i, j, t + 1)) return true;
		break;
	}
 
	for(auto [i, j] : adj[x][y]) ++moves[i][j];
 
	tms[x][y] = -1;
 
	return false;
}
 
void solve() {
 
	for(int x = 0; x < N; ++x) {
		for(int y = 0; y < N; ++y) {
			tms[x][y] = -1;
			for(auto [dx, dy] : delta) {
				int i = dx + x, j = dy + y;
				if(i < 0 || j < 0 || i >= 8 || j >= 8) continue;
				adj[x][y].pb({i, j});
			}
			moves[x][y] = adj[x][y].size();
		}
	}
 
	cin >> xi >> yi;
 
	swap(xi, yi);
	--xi, --yi;
 
	backtrack(xi, yi, 1);
 
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j)
			cout << tms[i][j] << ' ';
		cout << '\n';
	}
}	
 
int main() {
    ios_base :: sync_with_stdio(false);
   // cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}
