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

struct Hopcraft {
	vector<vector<ii>> g;
	vector<int> odd, fr, first, sat;
	vector<ii> p;
	queue<ii> q;
	int n, m {}, mat {};

	Hopcraft(int n) : n {n} {
		g.resize(n);
		odd.assign(n, -1);
		p.resize(n);
		fr.assign(n, true);
		first.resize(n);
	}
	
	void add_edge(int u, int v) {
		g[u].emplace_back(v, m);
		g[v].emplace_back(u, m);
		++m;
	}

	void dfs(int v, int x) {
		if(odd[v] != -1) return;
		odd[v] = x;
		for(auto& edge : g[v]) dfs(edge.first, 1 ^ x);
	}
	
	bool bfs() {
		bool flag = false;
		
		fill(first.begin(), first.end(), -1);
		
		for(int v = 0; v < n; ++v) {
			if(odd[v] || !fr[v]) continue;
			q.push({v, 0});
			p[v] = {v, -1};
			first[v] = v;
		}
		
		while(!q.empty()) {
			int v = q.front().first, t = q.front().second;
			int w = first[v];
			q.pop();
			
			if(!fr[w]) continue;
			
			else if(t && fr[v]) {
				flag = true;
				fr[v] = fr[w] = false;
				++mat;
				for(; ; t ^= 1) {
					int u = p[v].first, e = p[v].second;
					if(u == v) break;
					sat[e] = t;
					v = u;
				}
				continue;
			}
			
			for(auto& edge : g[v]) {
				int u = edge.first, e = edge.second;
				if(first[u] != -1 || sat[e] != t) continue;
				p[u] = {v, e};
				first[u] = w;
				q.push({u, t ^ 1});
			}
		}
		
		return flag;
	}
	
	auto matching() {
		for(int v = 0; v < n; ++v) dfs(v, 0);
		sat.assign(m, 0);
		while(bfs());	
		return mat;
	}
};


void solve() {
	int n;

	cin >> n;

	map<string, int> id;
	vector<vector<int>> lista(n);
	map<vector<int>, int> label;
	int v = 0;

	for(int i = 0; i < n; ++i) {
		int m;
		cin >> m;
		lista[i].resize(m);
		for(int j = 0; j < m; ++j) {
			string algo;
			cin >> algo;
			if(!id.count(algo)) id[algo] = id.size();
			lista[i][j] = id[algo];
		}
		sort(lista[i].begin(), lista[i].end());
		v += (1 << m) - 1;
	}

	Hopcraft hop(2 * v);

	for(auto& a : lista) {
		int m = a.size();

		vector<int> lb(1 << m);

		for(int k = 1; k < (1 << m); ++k) {
			vector<int> b;

			for(int j = k; j; j -= j & -j) {
				int i = __builtin_ctz(j);
				b.push_back(a[i]);
			}

			if(!label.count(b)) label[b] = label.size();

			lb[k] = label[b];

			if(!(k & (k - 1))) continue;

			for(int j = k; j; j -= j & -j) {
				int i = __builtin_ctz(j);
				hop.add_edge(lb[k ^ (1 << i)], v + lb[k]);
			}
		}
	}

	cout << (int)label.size() - hop.matching() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}