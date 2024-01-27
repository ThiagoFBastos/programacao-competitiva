#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
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

const int N = 5e2 + 10;

i64 dp[N][N];

void solve() {
	int n, s1, s2;
	cin >> n >> s1 >> s2;
	for(int i = 0; i <= s1; ++i)
		for(int j = 0; j <= s2; ++j)
			dp[i][j] = INFLL;
	dp[0][0] = 0;
	vector<tuple<int, int, int, int>> a(n);
	for(auto& [x, t, y, r] : a) cin >> x >> t >> y >> r;
	sort(all(a));
	for(auto [x, t, y, r] : a) {
		for(int a = s1; a >= 0; --a) {
			for(int b = s2; b >= 0; --b) {
				i64 v = dp[a][b];
				i64& Y = dp[a][min(b + y, s2)];
				i64& X = dp[min(s1, a + x)][min(s2, b + (a<s1)*max(0, a + x - s1))];
				X = min(X, v + t);
				Y = min(Y, v + r);
			}
		}
	}
	if(dp[s1][s2] > 1e15L) cout << "-1\n";
	else cout << dp[s1][s2] << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
