#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,mmx,sse2")
#include <bits/stdc++.h>


using namespace std;

#define x first
#define y second

using ii = pair<int, int>;

const int maxn = 1e3 + 3, mod = 1e9 + 7;

int C[maxn][maxn], ans[maxn];
ii dp[maxn];

int mod_sum(int x) {
	return x >= mod ? x - mod : x;
}

void solve() {
	int n;
	cin >> n;
	
	vector<ii> p(n), cnt;
	
	for(int i = 0; i < n; ++i)
		cin >> p[i].x >> p[i].y;
		
	sort(p.begin(), p.end());
	
	for(int i = 0; i < n; ++i)
		for(int k = i + 1; k < n; ++k)
			cnt.emplace_back(p[i].x + p[k].x, p[i].y + p[k].y);
			
	sort(cnt.begin(), cnt.end());
	
	for(int i = 0; i <= n; ++i) {
		C[i][0] = C[i][i] = 1;
		for(int k = 1; k < n; ++k)
			C[i][k] = mod_sum(C[i - 1][k] + C[i - 1][k - 1]);
	}
	
	ans[1] = n;
	
	int lo = 0;
	for(int i = 0, k; i < (int)cnt.size(); i = k) {
		k = i;
		while(k < (int)cnt.size() && cnt[k] == cnt[i]) ++k;
		++dp[k - i].x;
		while(lo < n && make_pair(2 * p[lo].x, 2 * p[lo].y) < cnt[i]) ++lo;
		if(lo < n && 2 * p[lo].x == cnt[i].x && 2 * p[lo].y == cnt[i].y) ++dp[k - i].y;
	}
	
	for(int k = 1; k <= n / 2; ++k) {
		for(int i = 1; i <= k; ++i) {
			ans[i << 1] = (ans[i << 1] + 1ll * dp[k].x * C[k][i]) % mod;
			ans[(i << 1) | 1] = (ans[(i << 1) | 1] + 1ll * dp[k].y * C[k][i]) % mod; 
		}
	}
	
	for(int i = 1; i < n; ++i) cout << ans[i] << ' ';
	cout << ans[n] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}