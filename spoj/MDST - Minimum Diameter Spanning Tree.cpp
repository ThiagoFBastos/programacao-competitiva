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

const int N = 1e3 + 10;

vector<int> adj[N], t[N];
vector<tuple<int, int, int>> path[N];

int n, deg[N], tim[N], id[N];
bool vis[N];

void getPath(int v) {
	queue<int> q;
	path[v].clear();
	memset(tim, -1, sizeof(int) * n);
	q.push(v);
	tim[v] = 0;
	path[v].emplace_back(v, 0, -1);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int w : adj[u]) {
			if(tim[w] != -1) continue;
			tim[w] = 1 + tim[u];
			path[v].emplace_back(w, tim[w], u);
			q.push(w);
		}
	}
}

int diameter(int n) {
	queue<int> q;
	int dim = -1, cnt = 0;
	for(int u = 0; u < n; ++u) {
		deg[u] = t[u].size();
		if(deg[u] <= 1) tim[u] = 0, q.push(u);
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		if(dim < tim[u]) dim = tim[u], cnt = 1;
		else if(dim == tim[u]) ++cnt;
		for(int v : t[u]) {
			if(--deg[v] != 1) continue;
			tim[v] = 1 + tim[u];
			q.push(v);
		}
	}
	return 2 * dim + cnt - 1;
}

int minimum_diameter() {
	int dim = INT_MAX, ex = INT_MAX;

	for(int u = 0; u < n; ++u) {
		getPath(u);
		ex = min(ex, get<1>(path[u].back()));
	}

	for(int u = 0; u < n; ++u) {

		if(get<1>(path[u].back()) != ex) continue;

		for(int v = 0; v < n; ++v) t[v].clear();

		for(auto& k : path[u]) {
			int v, d, p;
			tie(v, d, p) = k;
			if(p < 0) continue;
			t[v].push_back(p);
			t[p].push_back(v);
		}

		dim = min(dim, diameter(n));

		for(int v : adj[u]) {
			if(v > u || ex != get<1>(path[v].back())) continue;

			for(int w = 0; w < n; ++w) {
				if(w > u) id[w] = w - 1;
				else if(w == u) id[w] = v;
				else id[w] = w;	
				t[w].clear();
			}

			memset(vis, 0, n * sizeof(bool));

			vis[u] = vis[v] = true;

			for(int i = 0, j = 0, X = u, Y = v; i < n && j < n; ) {
				int vu, du, pu, vv, dv, pv;

				tie(vu, du, pu) = path[X][i];
				tie(vv, dv, pv) = path[Y][j];

				if(du > dv) {
					swap(i, j);
					swap(X, Y);
					swap(vu, vv);
					swap(pu, pv);
				}

				if(!vis[vu]) {
					vis[vu] = true;
					t[id[vu]].push_back(id[pu]);
					t[id[pu]].push_back(id[vu]);
				}

				++i;
			}

			dim = min(dim, 1 + diameter(n - 1));
		}
	}
	
	return dim;
}

void solve() {
	cin >> n;
	for(int i = 0; i < n; ++i) adj[i].clear();
	for(int i = 0; i < n; ++i) {
		int v, k;
		cin >> v >> k;
		--v;
		while(k--) {
			int u;
			cin >> u;
			--u;
			adj[v].push_back(u);
		}
	}
	cout << minimum_diameter() << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}