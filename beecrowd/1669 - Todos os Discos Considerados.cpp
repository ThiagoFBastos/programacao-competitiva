#include "bits/stdc++.h"
using namespace std;
int n[2], d;
vector<vector<int>> g;
vector<int> degree;
int solve(int k) {
	queue<int> X[2];
	int ans = 0;
	fill(degree.begin(), degree.end(), 0);
	for(vector<int>& adj : g)
		for(int u : adj)
			++degree[u];
	for(int i = 0; i < n[0]; ++i) if(degree[i] == 0) X[0].push(i);
	for(int i = n[0]; i < n[0] + n[1]; ++i) if(degree[i] == 0) X[1].push(i);
	for(int x = n[0] + n[1], t = k; x > 0; ++ans, t ^= 1) {
		while(!X[t].empty()) {
			int u = X[t].front();
			X[t].pop();
			--x;
			for(int v : g[u]) {
				if(--degree[v] == 0) 
					X[v >= n[0]].push(v);
			}
		}
	}
	return ans + 1;
}

int solve() {
	return min(solve(0), solve(1));	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true) {
		cin >> n[0] >> n[1] >> d;
		if(!(n[0] or n[1] or d)) break;
		degree.assign(n[0] + n[1], 0);
		g.clear();
		g.resize(n[0] + n[1]);
		for(int i = 0; i < d; ++i) {
			int x, y;
			cin >> x >> y;
			--x, --y;
			g[y].push_back(x);
		}
		cout << solve() << '\n';
	}
	return 0;
}