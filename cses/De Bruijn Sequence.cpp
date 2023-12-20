#include "bits/stdc++.h"
using namespace std;
vector<vector<int>> g;
int n;
string str;
void tour(int v, int e = -1) {
	while(!g[v].empty()) {
		int u = g[v].back();
		g[v].pop_back();
		tour(u, u & 1);
	}
	if(e != -1) str += e + '0';
}
void solve() {
	cin >> n;
	if(n == 1) {
		cout << "01\n";
		return;
	}
	int p = 1 << (n - 1);
	g.resize(p);
	for(int i = 0; i < p; ++i)
		for(int j = 0; j < 2; ++j)
			g[i].push_back(2 * i % p + j);
	tour(0);
	str += string(n - 1, '0');
	cout << str << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
