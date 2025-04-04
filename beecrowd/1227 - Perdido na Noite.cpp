#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

int n, a, b, c;
vector<vector<int>> t;
vector<double> p, pc;
vector<int> pa;

void dfs(int v, int pai) {
	int dv = t[v].size();
	if(v == pai) pc[v] = 1.0;
	pa[v] = pai;
	p[v] = 0;
	for(int u : t[v]) {
		if(u == pai) continue;
		else if(u == b || u == c) {
			pa[u] = v;
			p[u] = 1.0;
			pc[u] = pc[v] / dv;
		} else {
			int du = t[u].size();
			pc[u] = pc[v] / dv;
			dfs(u, v);
			p[v] += p[u] / (dv * du);
		}
	}
	p[v] = 1.0 / (1.0 - p[v]);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(cin >> n >> a >> b >> c) {
		--a, --b, --c;
		t.resize(n);
		pc.resize(n);
		p.resize(n);
		pa.assign(n, -1);
		for(int i = 1; i < n; ++i) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			t[u].push_back(v);
			t[v].push_back(u);
		}
		dfs(a, a);
		double pe = 0;
		if(pa[b] != -1) {
			vector<int> path;
			for(int v = b; v != a; v = pa[v]) path.push_back(v);
			path.push_back(a);
			reverse(path.begin(), path.end());
			pe = 1.0;
			for(int v : path) {
				if(v == b) break;
				int dv = t[v].size();
				pe = pe * p[v] / dv;
			}
		}
		cout << fixed << setprecision(6) << pe << '\n';
		for(vector<int>& adj : t) adj.clear();
	}
	return 0;
}