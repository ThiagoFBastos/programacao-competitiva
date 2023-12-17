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

std::mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int N = 101;
vector<vector<int>> g[2];
vector<int> altura[2][N], pai[2];
int n[2], caso;

bool parecido[N][N];

void dfs(int t, int u, int p, int h) {
	altura[t][h].push_back(u);
	pai[t][u] = p;
	for(int v : g[t][u]) {
		if(v == p) continue;
		dfs(t, v, u, h + 1);
	}
}

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
	
	for(int i = 0; i < 2; ++i) {
		cin >> n[i];
		g[i].clear();
		g[i].resize(n[i]);
		pai[i].resize(n[i]);
		for(int j = 0; j < n[i]; ++j) altura[i][j].clear();
		for(int j = 1; j < n[i]; ++j) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			g[i][u].push_back(v);
			g[i][v].push_back(u);
		}
		dfs(i, 0, 0, 0);
	}
	
	for(int u = 0; u < n[0]; ++u)
	for(int v = 0; v < n[1]; ++v)
		parecido[u][v] = false;
		
	for(int h = n[1] - 1; h >= 0; --h) {
		for(int u : altura[0][h]) {
			for(int v : altura[1][h]) {
				auto& gu = g[0][u];
				auto& gv = g[1][v];
				Hopcraft hop(gu.size() + gv.size());
				for(int i = 0; i < (int)gu.size(); ++i) {
					int fu = gu[i];
					if(fu == pai[0][u]) continue;
					for(int j = 0; j < (int)gv.size(); ++j) {
						int fv = gv[j];
						if(fv == pai[1][v] || !parecido[fu][fv]) continue;
						hop.add_edge(i, j + (int)gu.size());
					}
				}
				parecido[u][v] = hop.matching() == ((int)gv.size() - (!!v));
			}
		}
	}
	
	cout << "Case " << ++caso << ": " << (parecido[0][0] ? "Yes\n" : "No\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}

