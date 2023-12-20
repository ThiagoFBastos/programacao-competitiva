#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int N = 1e5;
	int n, m;
	vector<int> G[N];
	cin >> n >> m;
	vector<int> d(n, 0);
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		G[u - 1].push_back(v - 1);
		++d[v - 1];
	}
	vector<int> out;
	queue<int> Q;
	for(int v = 0; v < n; ++v) {
		if(d[v] == 0)
			Q.push(v);
	}
	out.reserve(n);
	while(!Q.empty()) {
		int v = Q.front();
		Q.pop();
		out.push_back(v);
		for(int u : G[v]) {
			if(--d[u] == 0)
				Q.push(u);
		}
	}
	if(out.size() != n)
		cout << "IMPOSSIBLE\n";
	else {
		for(int v : out) cout << v + 1 << ' ';
		cout << '\n';
	}
	return 0;
}
