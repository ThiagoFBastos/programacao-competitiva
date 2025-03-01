#include "bits/stdc++.h"
using namespace std;
using ii = pair<int, int>;
int matching(vector<vector<ii>>& G, int edges) {
	int n = G.size(), cnt = 0;
	vector<bool> _free(n, true);
	vector<int> first(n), color(n, -1), sat(edges, 0);
	vector<ii> p(n);
	for(int v = 0; v < n; ++v) {
		if(color[v] != -1) continue;
		queue<int> q;
		q.push(v);
		color[v] = 0;
		while(!q.empty()) {
			int v = q.front();
			q.pop();
			for(auto& e : G[v]) {
				if(color[e.first] != -1) continue;
				color[e.first] = color[v] ^ 1;
				q.push(e.first);
			}
		}
	}
	while(true) {
		queue<ii> q;
		bool quit = true;
		fill(first.begin(), first.end(), -1);
		for(int v = 0; v < n; ++v) {
			if(color[v] || !_free[v]) continue;
			p[v] = {v, -1};
			first[v] = v;
			q.push({v, 0});
		}
		while(!q.empty()) {
			int u = q.front().first, t = q.front().second;
			q.pop();
			int v = first[u];
			if(!_free[v]) continue;
			else if(t && _free[u]) {
				_free[u] = _free[v] = false;
				++cnt;
				quit = false;
				for( ; ; t ^= 1) {
					int x = p[u].first, y = p[u].second;
					if(x == u) break;
					sat[y] ^= 1;
					u = x;
				}
				continue;
			}
			for(auto& e : G[u]) {
				int x = e.first, y = e.second;
				if(first[x] != -1 || sat[y] != t) continue;
				p[x] = {u, y};
				first[x] = v;
				q.push({x, t ^ 1});
			}
		}
		if(quit) break;
	}
	return cnt;
}
void solve() {
	int n, e = 0;
	cin >> n;
	vector<ii> p(n);
	vector<int> X(n), Y(n);
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		p[i] = {x, y};
		X[i] = x, Y[i] = y;
	}
	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());
	X.resize(unique(X.begin(), X.end()) - X.begin());
	Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
	for(auto& v : p) {
		v.first = lower_bound(X.begin(), X.end(), v.first) - X.begin();
		v.second = X.size() + int(lower_bound(Y.begin(), Y.end(), v.second) - Y.begin());
	}
	vector<vector<ii>> G(X.size() + Y.size());
	for(auto& v : p) {
		G[v.first].push_back({v.second, e});
		G[v.second].push_back({v.first, e++});
	}
	cout << matching(G, e) << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
