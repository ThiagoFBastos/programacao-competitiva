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

const int N = 3e3 + 10, MOD = 1e9 + 7;

int pre[N], C[N][N];

array<int, N> dp[2];

void solve() {
	int n, m;
	string s;

	cin >> n >> m >> s;
	
	for(int i = 0; i <= n; ++i) {
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}

	for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + s[i - 1] - '0';

	vector<int> l, r;
	int lo = -1, hi = -1;

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		if(b <= hi) continue;
		l.pb(a);
		r.pb(b);
		lo = a, hi = b;
	}

	int ans = 1;

	reverse(all(l));
	reverse(all(r));

	while(!l.empty()) {
		vector<int> L, R;
		int lo = -INF, hi = INF;
		
		while(!l.empty() && max(lo, l.back()) <= min(hi, r.back())) {
			L.pb(l.back());
			R.pb(r.back());
			lo = l.back(), hi = r.back();
			l.pop_back(); r.pop_back();
		}

		fill(all(dp[0]), 0);

		dp[0][0] = 1;

		int m = L.size();

		for(int i = 0; i < m; ++i) {
			int lo = i ? R[i - 1] + 1 : L[i];
			int hi = i + 1 < m ? L[i + 1] : R[i] + 1;

			int _1 = pre[R[i] + 1] - pre[lo];

			fill(all(dp[1]), 0);

			for(int j = 0; _1 + j <= n; ++j) {
				dp[1][_1 + j] += dp[0][j];
				if(dp[1][_1 + j] >= MOD) dp[1][_1 + j] -= MOD;
			}

			swap(dp[0], dp[1]);

			int len = hi - L[i];
	
			fill(all(dp[1]), 0);

			for(int j = 0; j <= n; ++j) {
				for(int k = 0; k <= min(j, len); ++k) {
					if(len - k + j > R[i] - L[i] + 1) continue;
					dp[1][j - k] = (dp[1][j - k] + 1ll * C[len][k] * dp[0][j]) % MOD;
				}
			}	
			
			swap(dp[0], dp[1]);
		}

		ans = 1ll * ans * dp[0][0] % MOD;
	}

	cout << ans << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
