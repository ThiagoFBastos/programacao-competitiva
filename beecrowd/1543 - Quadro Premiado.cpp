#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
const int N = 100, INF = -1e8;
inline ll cost(const char* s, int *v) {
	ll ans = 0;
	for(int k = 0; s[k]; ++k) {
		if(s[k] == '+') ans += v[k];
		else if(s[k] == '-') ans -= v[k];
	}
	return ans;
}
int main() {
	ios_base :: sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	int n, m, k, a[N][N];
	char p[N][N + 1];
	bool comb[N][N];
	ll dp[N][N];
	while(true) {
		cin >> n >> m;
		if(!(n || m)) break;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				cin >> a[i][j];
		cin >> k;
		for(int i = 0; i < k; ++i) cin >> p[i];
		for(int i = 0; i < k; ++i)
			for(int j = 0; j < k; ++j) comb[i][j] = false;
		for(int i = 0; i < k; ++i) {
			for(int j = i; j < k; ++j) {
				bool flag = true;
				for(int a = 0; a < m; ++a) {
					if(p[i][a] != '.' && p[j][a] == p[i][a]) {
						flag = false;
						break;
					}
				}
				comb[i][j] = comb[j][i] = flag;
			}
		}
		for(int i = 0; i < k; ++i) dp[0][i] = cost(p[i], a[0]);
		for(int i = 1; i < n; ++i) {
			for(int j = 0; j < k; ++j) {
				ll r = INF;
				dp[i][j] = cost(p[j], a[i]);
				for(int a = 0; a < k; ++a) if(comb[a][j]) r = max(r, dp[i - 1][a]);
				dp[i][j] += r;
			}
		}
		cout << *max_element(dp[n - 1], dp[n - 1] + k) << '\n';
	}
	return 0;
}