#include <bits/stdc++.h>

using namespace std;

#define FOR(k, a, b) for(int k = (a); k < (b); ++k)
#define REP(k, a, b) for(int k = (a); k > (b); --k)

#define all(x) x.begin(), x.end()
#define up(x, y) upper_bound(all(x), y)
#define lower(x, y) lower_bound(all(x), y)
#define INF 0x3ffffff
#define fi first
#define sc second

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

typedef unsigned long long ull;
typedef long long ll;

#define MAXN 50

struct estado {

	int x0, y0;
	int x1, y1;
};

int main() {

	int tests;
	char map1[MAXN][MAXN + 1], map2[MAXN][MAXN + 1];
	
	scanf("%d", &tests);
		
	while(tests--) {
	
		int n, m, x0, y0, x1, y1, z0, w0, z1, w1;
		
		scanf("%d%d", &n, &m);
		
		FOR(k, 0, n) scanf("%s", map1[k]);
		FOR(k, 0, n) scanf("%s", map2[k]);
		
		FOR(k, 0, n) {
		
			FOR(i, 0, m) {
			
				if(map1[k][i] == 'R') x0 = k, y0 = i;
				else if(map1[k][i] == 'F') x1 = k, y1 = i;
				
				if(map2[k][i] == 'R') z0 = k, w0 = i;
				else if(map2[k][i] == 'F') z1 = k, w1 = i;
			}
		}
		
		int N = n * m;
		
		int **dp = new int*[N];
		
		FOR(k, 0, N) {
		
			dp[k] = new int[N];
			memset(dp[k], -1, N * sizeof(int));
		}
		
		queue<estado> Q;
		
		Q.push({x0, y0, z0, w0});
		
		dp[x0 * m + y0][z0 * m + w0] = 0;
		
		while(!Q.empty()) {
		
			auto [x0, y0, z0, w0] = Q.front();
			
			Q.pop();
			
			int mov = 1 + dp[x0 * m + y0][z0 * m + w0];
			
			if(map1[x0][y0] == 'F' && map2[z0][w0] == 'F')
				break;
				
			else if(mov == 51 || map1[x0][y0] == 'B' || map2[z0][w0] == 'B') 
				continue;
			
			int x = x0, z = z0;
			
			if(z && x) {
			
				if(map1[x - 1][y0] != '#') --x;
				if(map2[z - 1][w0] != '#') --z;
			}
			
			if(dp[x * m + y0][z * m + w0] == -1) {
			
				dp[x * m + y0][z * m + w0] = mov;
				Q.push({x, y0, z, w0});
			}
			
			x = x0, z = z0;
			
			if(x < n - 1 && z < n - 1) {
	
				if(map1[x + 1][y0] != '#') ++x;
				if(map2[z + 1][w0] != '#') ++z;
			}
			
			if(dp[x * m + y0][z * m + w0] == -1) {
			
				dp[x * m + y0][z * m + w0] = mov;
				Q.push({x, y0, z, w0});
			}
			
			int y = y0, w = w0;
			
			if(w && y) {
			
				if(map1[x0][y - 1] != '#') --y;
				if(map2[z0][w - 1] != '#') --w;
			}
				 
			if(dp[x0 * m + y][z0 * m + w] == -1) {
			
				dp[x0 * m + y][z0 * m + w] = mov;
				Q.push({x0, y, z0, w});
			}
			
			y = y0, w = w0;
			
			if(y < m - 1 && w < m - 1) {
			
				if(map1[x0][y + 1] != '#') ++y;
				if(map2[z0][w + 1] != '#') ++w;
			}
			
			if(dp[x0 * m + y][z0 * m + w] == -1) {
			
				dp[x0 * m + y][z0 * m + w] = mov;
				Q.push({x0, y, z0, w});
			}
		}
		
		if(dp[x1 * m + y1][z1 * m + w1] == -1)
			puts("impossivel");
			
		else
			printf("%d\n", dp[x1 * m + y1][z1 * m + w1]);
		
		FOR(k, 0, N)
			delete[] dp[k];
		
		delete[] dp;
	}
	
	return 0;
}