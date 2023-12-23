#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int mod = 998244353;
const int N = 64;

int a[N][N], tmp[N][N], n, x;

int count() {
	vector<vector<int>> g(n);
	vector<bool> vis(n, false);
	int fat, ans = 1, w;

	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			bool flag = true;
			for(int k = 0; k < n; ++k)
				flag = flag && a[i][k] + a[j][k] <= x;
			if(!flag) continue;
			g[i].push_back(j);
			g[j].push_back(i);
		}
	}

	
	function<void(int)> dfs = [&](int u) {
		vis[u] = true;
		++w;
		fat = (i64)fat * w % mod;
		for(int v : g[u]) {
			if(vis[v]) continue;
			dfs(v);
		}
	};

	for(int i = 0; i < n; ++i) {
		if(vis[i]) continue;
		fat = 1, w = 0;
		dfs(i);	
		ans = (i64)ans * fat % mod;
	}
		
	return ans;
}

void solve() {
	
	cin >> n >> x; 

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		cin >> a[i][j];

	int ans = count();

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		tmp[j][i] = a[i][j];

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		a[i][j] = tmp[i][j];

	cout << (i64)ans * count() % mod  << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
