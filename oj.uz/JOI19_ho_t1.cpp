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
 
void solve() {				
	int n, m;
	
	cin >> n >> m;
	
	vector<string> g(n);
	
	auto cols = vector<vector<int>>(n + 1, vector<int>(m));
	auto rows = vector<vector<int>>(n, vector<int>(m + 1));
	i64 cnt = 0;
	
	fill(cols[0].begin(), cols[0].end(), 0);
	
	for(int i = 0; i < n; ++i) {
		cin >> g[i];
		rows[i][0] = 0;
		for(int j = 0; j < m; ++j) {
			rows[i][j + 1] = rows[i][j];
			cols[i + 1][j] = cols[i][j];
			if(g[i][j] == 'O') ++rows[i][j + 1];
			else if(g[i][j] == 'I') ++cols[i + 1][j];
		}
	}
	
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(g[i][j] != 'J') continue;
			cnt += (0ll + rows[i][m] - rows[i][j]) * (cols[n][j] - cols[i][j]); 
		}
	}
	
	cout << cnt << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
