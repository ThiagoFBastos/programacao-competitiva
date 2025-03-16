#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

vector<vector<int>> g[2]; 
vector<int> max_dist[2], max_lv[2], lv[2];
int n[2];

void dfs(int k, int v, int pai) {
	max_lv[k][v] = lv[k][v];	
	for(int u : g[k][v]) {
		if(u == pai) continue;
		lv[k][u] = 1 + lv[k][v];
		dfs(k, u, v);
		max_lv[k][v] = max(max_lv[k][v], max_lv[k][u]);
	}
}

void dfs(int k, int v, int pai, int h) {
	int p = 0, q = 0;
	max_dist[k][v] = max(lv[k][v] + h, max_lv[k][v] - lv[k][v]);
	for(int u : g[k][v]) {
		if(u == pai) continue;
		else if(p < max_lv[k][u]) q = p, p = max_lv[k][u];
		else if(q < max_lv[k][u]) q = max_lv[k][u];
	}
	for(int u : g[k][v]) {
		if(u == pai) continue;
		dfs(k, u, v, max(h, (p == max_lv[k][u] ? q : p) - 2 * lv[k][v])); 
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cout.precision(3);
	cout.setf(ios_base :: fixed);
	while(cin >> n[0] >> n[1]) {
		for(int i = 0; i < 2; ++i) {
			g[i].resize(n[i]);
			max_dist[i].resize(n[i]);
			lv[i].resize(n[i]);
			max_lv[i].resize(n[i]);
		}
		for(int i = 0; i < 2; ++i) {
			for(int j = 1; j < n[i]; ++j) {
				int a, b;
				cin >> a >> b;
				--a, --b;
				g[i][a].push_back(b);
				g[i][b].push_back(a);
			}
			lv[i][0] = 0;
			dfs(i, 0, -1);
			dfs(i, 0, -1, 0);
		}
		long long sum = 0;
		int diam, lo = n[1];
		vector<long long> p(n[1] + 1);
		for(int i = 0; i < 2; ++i) sort(max_dist[i].begin(), max_dist[i].end());
		diam = max(max_dist[0].back(), max_dist[1].back());
		p[0] = 0;
		for(int i = 1; i <= n[1]; ++i) p[i] = p[i - 1] + max_dist[1][i - 1];
		for(int dist : max_dist[0]) {
			while(lo > 0 && dist + max_dist[1][lo - 1] >= diam) --lo;
			sum += 1LL * lo * diam + p[n[1]] - p[lo] + (1LL + dist) * (n[1] - lo);
		}
		cout << sum / (double)(n[0] * n[1]) << '\n';
		for(int i = 0; i < 2; ++i)
			for(vector<int>& adj : g[i])
				adj.clear();
	}
	return 0;
}