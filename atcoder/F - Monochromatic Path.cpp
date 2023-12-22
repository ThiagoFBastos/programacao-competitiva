#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e3;
const i64 INF = 1e16L;

i64 dp[N][N][2][2];

void solve() {

	int h, w;

	cin >> h >> w;

	vector<int> r(h), c(w);

	for(int& v : r) cin >> v;
	for(int& v : c) cin >> v;

	vector<string> g(h);

	for(auto& s : g) cin >> s;

	for(int i = 0; i < h; ++i)
	for(int j = 0; j < w; ++j)
	for(int a = 0; a < 2; ++a)
	for(int b = 0; b < 2; ++b)
		dp[i][j][a][b] = INF;

	for(int a = 0; a < 2; ++a) {
		for(int b = 0; b < 2; ++b) {
			i64 X = 0;
			if(a) X += r[0];
			if(b) X += c[0];
			dp[0][0][a][b] = X;
		}
	}

	for(int i = 0; i < h; ++i) {
		for(int j = 0; j < w; ++j) {
			for(int a:{0,1}) {
				for(int b:{0,1}) {
					int c1 = (g[i][j] - '0') ^ a ^ b;
					
					if(i + 1 < h) {
						int c2 = (g[i + 1][j] - '0') ^ b;	
						if(c1 != c2)
							dp[i+1][j][1][b]=min(dp[i+1][j][1][b],dp[i][j][a][b]+r[i+1]);
						else
							dp[i+1][j][0][b]=min(dp[i+1][j][0][b],dp[i][j][a][b]);
					}

					if(j + 1 < w) {
						int c2 = (g[i][j+1] - '0') ^ a;	
						if(c1 != c2)
							dp[i][j+1][a][1]=min(dp[i][j+1][a][1],dp[i][j][a][b]+c[j+1]);
						else
							dp[i][j+1][a][0]=min(dp[i][j+1][a][0],dp[i][j][a][b]);
					}
				}
			}
		}
	}

	i64 ans=INF;
	for(int a:{0,1})
	for(int b:{0,1})
		ans=min(ans,dp[h-1][w-1][a][b]);

	cout<<ans<<'\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
