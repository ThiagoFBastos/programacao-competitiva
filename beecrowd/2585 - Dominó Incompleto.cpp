#pragma GCC optimize("O3")
#pragma GCC target("popcnt")

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
 
const int N = 10, INF = 1e9;
int adj[N], dp[1<<N][1<<N];

void solve() {
	int n, ans = 1;

	cin >> n;
	
	if(cin.eof()) exit(0);

	memset(adj, 0, sizeof adj);

	for(int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		adj[a] |= 1 << b;
		adj[b] |= 1 << a;
	}

	for(int i=0;i<(1<<N);++i)
	for(int j=0;j<(1<<N);++j)
		dp[i][j] = -INF;

	for(int i = 0; i < N; ++i) {
		if(!adj[i]) continue;
		dp[1<<i][0] = !!(adj[i]&(1<<i));
	}

	for(int i=1;i<(1<<N);++i) {
		for(int a=~i&1023;a;a-=a&-a) {
			int u = __builtin_ctz(a);
			int X = (1<<u)|i;
			for(int j = i; j >= 0; j = (j - 1) & i) {
				if(dp[i][j] >= 0){
					int mask = i & adj[u];
					for(int S = mask; S; S = (S - 1) & mask) {
						int bits = __builtin_popcount(S);
						int Y = j^S^((bits&1)<<u);
						dp[X][Y] = max(dp[X][Y], dp[i][j]+bits+(!!(adj[u]&(1<<u))));
					}
				}
				if(!j) break;
			}
		}
	}

	for(int i=0;i<(1<<N);++i) {
		for(int j=0;j<(1<<N); ++j) {
			int bits = __builtin_popcount(j);
			if(bits!=2&&bits)continue;
			ans = max(ans, dp[i][j]);
		}
	}

	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(true) solve();
	return 0;
}