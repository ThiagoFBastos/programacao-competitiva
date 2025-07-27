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
using i128 = __int128;

const int N = 1e3 + 10, M = 1e6 + 10;

int c, r, cost[N][N], vis[N][N];
vector<ii> pq[M];

int jumps[][5] = {
	{7, 6, 5, 6, 7},	
	{6, 3, 2, 3, 6},
	{5, 2, 0, 2, 5},	
	{6, 3, 2, 3, 6},
	{7, 6, 5, 6, 7}
};

void solve() {

	while(true) {
		cin >> c >> r;

		if(c + r == 0) break;

		int cf, rf, ct, rt, m;

		cin >> cf >> rf >> ct >> rt;

		for(int i = 1; i <= c; ++i)
			for(int j = 1; j <= r; ++j)
				vis[i][j] = 0;

		cin >> m;

		while(m--) {
			int c1, r1, c2, r2;
			cin >> c1 >> r1 >> c2 >> r2;
			++vis[c1][r1];
			--vis[c1][r2+1];
			--vis[c2+1][r1];
			++vis[c2+1][r2+1];
		}

		for(int i = 1; i <= c; ++i) {
			for(int j = 1; j <= r; ++j) {
				vis[i][j] += vis[i - 1][j] + vis[i][j - 1] - vis[i - 1][j - 1];
				cost[i][j] = INF;
			}
		}

		int cur = 0, len = 1;

		cost[cf][rf] = 0;
		pq[0].pb({cf, rf});
		
		while(len) {
			while(pq[cur].empty()) ++cur;
			auto [xt, yt] = pq[cur].back(); pq[cur].pop_back();
			--len;
			if(vis[xt][yt]) continue;
			vis[xt][yt] = 1;
			for(int dx : {-2, -1, 0, 1, 2}) {
				for(int dy : {-2, -1, 0, 1, 2}) {
					int xf = xt + dx, yf = yt + dy;
					if(xf <= 0 || yf <= 0 || xf > c || yf > r) continue;	
					int new_cost = cost[xt][yt] + jumps[2+dx][2+dy];
					if(cost[xf][yf] <= new_cost) continue;
					cost[xf][yf] = new_cost;
					pq[new_cost].pb({xf, yf});
					++len;
				}
			}
		}

		if(cost[ct][rt] == INF) cout << "impossible\n";
		else cout << cost[ct][rt] << '\n';
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
