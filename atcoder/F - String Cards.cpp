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

const int N = 51;

string dp[N][N*N];

void solve() {
	int n, k;

	cin >> n >> k;

	vector<string> s(n);

	for(auto& v : s) cin >> v;

	sort(all(s), [](string a, string b) {
		return a + b < b + a;
	});

	for(int i = 0; i <= k; ++i)
		for(int j = 0; j <= n * 50; ++j)
			dp[i][j] = string(1, 'z' + 1);

	dp[0][0] = "";

	for(int i = 1; i <= n; ++i) {
		int m = s[i - 1].size();
		for(int j = k - 1; j >= 0; --j)
			for(int l = 0; l <= n * 50; ++l)
				dp[j + 1][l + m] = min(dp[j + 1][l + m], dp[j][l] + s[i - 1]);
	}

	string ans(1, 'z' + 1);

	for(int l = 1; l <= n * 50; ++l) ans = min(ans, dp[k][l]);

	cout << ans << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
