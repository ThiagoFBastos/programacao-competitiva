#include "bits/stdc++.h"
using namespace std;
int n, m;
struct BIT {
	vector<int> bit;
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	void upd(int k, int x) {
		for(; k < int(bit.size()); k += k & -k) bit[k] = max(bit[k], x);
	}
	int query(int k) {
		int ans = 0;
		for(; k > 0; k -= k & -k) ans = max(ans, bit[k]);
		return ans;
	}
};
int solve(vector<int>& s, vector<int>& t) {
	map<int, int> p;
	BIT bit(s.size());
	for(int i = 0; i < (int)s.size(); ++i) p[s[i]] = 1 + i;
	for(int i = 0; i < (int)t.size(); ++i) {
		auto k = p.find(t[i]);
		if(k != p.end()) bit.upd(k->second, 1 + bit.query(k->second)); 
	}
	return int(t.size()) + int(s.size()) - 2 * bit.query(s.size());
}
int matching(vector<vector<pair<int, int>>>& G, int edges) {
	int mat = 0;
	vector<bool> emp(edges, false), F(G.size(), true);
	vector<int> fi(G.size());
	vector<pair<int, int>> pai(G.size());
	while(true) {
		bool quit = true;
		queue<pair<int, int>> Q;
		fill(fi.begin(), fi.end(), -1);
		for(int i = 0; i < n; ++i) {
			if(F[i]) {
				fi[i] = i;
				pai[i] = {i, -1};
				Q.push({i, 0});
			}	
		}
		while(!Q.empty()) {
			auto [v, t] = Q.front();
			Q.pop();
			int u = fi[v];
			if(F[u]) {
				if(t && F[v]) {
					F[u] = F[v] = false;
					++mat;
					quit = false;
					for(int w = v; w != pai[w].first; w = pai[w].first, t ^= 1) emp[pai[w].second] = t;
				} else {
					for(auto [w, e] : G[v]) {
						if(fi[w] == -1 && emp[e] == t) {
							fi[w] = u;
							pai[w] = {v, e};
							Q.push({w, t ^ 1});
						}
					}
				}
			}
		}
		if(quit) break;
	}
	return mat;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	vector<int> cnt(26);
	cout.precision(2);
	cout.setf(ios_base :: fixed);
	while(true) {
		cin >> n >> m;
		if(!n) break;
		vector<vector<int>> X(n), Y(m);
		for(int i = 0; i < n; ++i) {
			string s;
			cin >> s;
			fill(cnt.begin(), cnt.end(), 0);
			X[i].resize(s.size());
			for(int j = 0; j < int(s.size()); ++j) X[i][j] = s[j] - 'A' + 26 * cnt[s[j] - 'A']++;
		}
		for(int i = 0; i < m; ++i) {
			string t;
			cin >> t;
			fill(cnt.begin(), cnt.end(), 0);
			Y[i].resize(t.size());
			for(int j = 0; j < int(t.size()); ++j) Y[i][j] = t[j] - 'A' + 26 * cnt[t[j] - 'A']++;
		}
		vector<vector<pair<int, int>>> G(n + m);
		int edges = 0;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				int ans = solve(X[i], Y[j]);
				if(ans % 5 == 0) {
					G[i].push_back({j + n, edges});
					G[j + n].push_back({i, edges++});
				}
			}
		}
		cout << "P = " << 100.0 * matching(G, edges) / n << '\n';
	}
	return 0;
}
