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

const int N = 5e5 + 100;

int n;
vector<int> g[N], l;

void dfs(int u, int p, int side) {
	int c = (int)g[u].size();
	int t = side, i = 0;
	for(; i < c;++i) {
		int v = g[u][i];
		if(v == p) continue;
		if(t * 2 >= c) break;
		++t;
		dfs(v, u, 0);
	}
	l.push_back(u);
	for(; i < c; ++i) {
		int v = g[u][i];
		if(v == p) continue;
		dfs(v, u, 1);
	}
}

void solve() {
	cin >> n;
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0, 0, 0);
	for(int v : l) cout << v << ' ';
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

