#include "bits/stdc++.h"

using namespace std;

using ll = long long;

int g[50][50];

void solve() {
	int n, m, a, b;
	
	cin >> n >> m >> a >> b;
	
	if(min(a, b) < m + n - 1) {
		cout << "Impossible\n";
		return;
	}
	
	cout << "Possible\n";
	
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < m; ++j)
		g[i][j] = 1;
		
	g[n - 1][m - 1] += a - (m + n - 1);
	g[n - 1][0] += b - (m + n - 1);
	
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m - 1; ++j) cout << g[i][j] << ' ';
		cout << g[i][m - 1] << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
 	return 0;
}
