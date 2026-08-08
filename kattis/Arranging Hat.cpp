#include "bits/stdc++.h"

using namespace std;

const int inf = 1e9;

int dp[41][41][401][11], n, m;
vector<string> a;

int rec(int k, int d, int L, int R) {
	if(dp[L][R][k][d] != -1) return dp[L][R][k][d];

	int ans = inf, swaps = 0;
	dp[L][R][k][d] = ans;	
		
	for(int i = L; i <= R; ++i) {
		swaps += a[k][i] != d + '0';
		ans = min(ans, swaps + rec(k + 1, 0, L, i) + rec(k, d + 1, i + 1, R));
	}
	
	return dp[L][R][k][d] = min(ans, rec(k, d + 1, L, R));
}

void build(int k, int d, int L, int R) {
	if(k == m || L > R) return;
	
	int swaps = 0;
	
	for(int i = L; i <= R; ++i) {
		swaps += a[k][i] != d + '0';
		int ans = swaps + dp[L][i][k + 1][0] + dp[i + 1][R][k][d + 1];
		if(ans == dp[L][R][k][d]) {
			for(int j = L; j <= i; ++j) a[k][j] = d + '0';
			build(k + 1, 0, L, i);
			build(k, d + 1, i + 1, R);
			return;
		}
	}
	
	build(k, d + 1, L, R);
}

void solve() {
	
	cin >> n >> m;
	
	vector<string> A(n);

	
	a.resize(m);
	
	for(int i = 0; i < m; ++i) a[i].resize(n);
	
	for(int i = 0; i < n; ++i) {
		cin >> A[i];
		for(int j = 0; j < m; ++j) a[j][i] = A[i][j];
	}
	
	for(int L = 0; L <= n; ++L) {
		for(int R = 0; R <= n; ++R) {
			for(int i = 0; i <= m; ++i) {
				for(int j = 0; j <= 10; ++j) {
					if(L > R || i == m) dp[L][R][i][j] = 0;
					else if(j == 10) dp[L][R][i][j] = inf;
					else dp[L][R][i][j] = -1;
				}
			}
		}
	}
		
	rec(0, 0, 0, n - 1);
	build(0, 0, 0, n - 1);
	
	for(int i = 0; i < m; ++i)
	for(int j = 0; j < n; ++j)
		A[j][i] = a[i][j];
		
	for(string& w : A) cout << w << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}