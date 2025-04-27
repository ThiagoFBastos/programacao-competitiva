#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
const int N = 50000;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	vector<int> G[N];
	int in_degree[N], top[N], k = 0, cnt = 0, n, m;
	priority_queue<int, vector<int>, greater<int>> pq;
	cin >> n >> m;
	for(int i = 0; i < n; ++i) in_degree[i] = 0;
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		++in_degree[v];
		G[u].push_back(v);
	}
	for(int v = 0; v < n; ++v) {
		if(in_degree[v] == 0) 
			pq.push(v);
	}
	while(!pq.empty()) {
		int v = pq.top();
		pq.pop();
		++cnt;
		top[k++] = v;
		for(int u : G[v]) {
			if(--in_degree[u] == 0)
				pq.push(u);
		}
	}
	if(cnt == n) for(int i = 0; i < n; ++i) cout << top[i] << '\n';
	else
		cout << "*\n";
	return 0;
}