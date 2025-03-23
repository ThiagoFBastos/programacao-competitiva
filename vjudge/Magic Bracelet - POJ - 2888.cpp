#include <iostream> 
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
/*
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;	
*/

const int MOD = 9973, N = 10;

int good[N][N];

int n, m, k;

void mul(int a[][N], int b[][N], int n) {
	int c[N][N];

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			long long X = 0;
			for(int k = 0; k < n; ++k)
				X += a[i][k] * b[k][j];
			c[i][j] = X % MOD;
		}
	}

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		a[i][j] = c[i][j];
}

long long intPow(long long n, int p) {
	long long ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % MOD;
		n = n * n % MOD;
	}
	return ans;
}

void matrix_pow(int dest[][N], int src[][N], int p, int n) {
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		dest[i][j] = i == j;

	for(; p > 0; p >>= 1) {
		if(p & 1) mul(dest, src, n);
		mul(src, src, n);
	}
}

void solve() {

	cin >> n >> m >> k;

	for(int i = 0; i < m; ++i)
	for(int j = 0; j < m; ++j)
		good[i][j] = 1;

	while(k--) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		good[a][b] = good[b][a] = 0;
	}

	vector<int> d;

	for(int i = 1; i * i <= n; ++i) {
		if(n % i) continue;
		d.pb(i);
		if(i * i != n) d.pb(n / i);
	}

	int l = d.size();

	sort(all(d));

	vector<int> cnt(l);
	int t[N][N], dp[N][N], ans = 0;

	for(int i = l - 1; i >= 0; --i) {
		cnt[i] = n / d[i];	
		for(int j = i + 1; j < l; ++j)
			if(d[j] % d[i] == 0) cnt[i] -= cnt[j];
	}

	for(int i = 0; i < l; ++i) {

		int times = 0;

		for(int k = 0; k < m; ++k)
			for(int j = 0; j < m; ++j)
				t[k][j] = good[k][j];
		
		matrix_pow(dp, t, d[i] - 1, m);
	
		for(int k = 0; k < m; ++k) {
			for(int j = 0; j < m; ++j) {
				times += dp[j][k] * good[k][j];
				if(times >= MOD) times -= MOD;
			}
		}
		
		ans = (ans + 1ll * cnt[i] * times) % MOD;
	}

	cout << ans * intPow(n, MOD - 2) % MOD << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}