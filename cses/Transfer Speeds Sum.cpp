#include <bits/stdc++.h>
 
using namespace std;
 
struct UF {
	vector<int> parent, rank, len;
 
	UF(int n) {
		parent.resize(n);
		rank.assign(n, 0);
		len.assign(n, 1);
 
		iota(parent.begin(), parent.end(), 0);
	}
 
	int find_set(int u) {
		return u == parent[u] ? u : parent[u] = find_set(parent[u]);
	}
 
	void join(int u, int v) {
		if(rank[u] > rank[v])
			swap(u, v);
 
		parent[u] = v;
		len[v] += len[u];
		rank[v] += rank[u] == rank[v]; 
	}
};
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
	vector<tuple<int, int, int>> edges;
	int64_t sum {};
 
	cin >> n;
 
	UF uf(n);
	
	for(int i = 1; i < n; ++i) {
		int a, b, x;
 
		cin >> a >> b >> x;
 
		edges.emplace_back(x, a - 1, b - 1);
	}
 
	sort(edges.rbegin(), edges.rend());
 
	for(auto [x, a, b] : edges) {
		a = uf.find_set(a);
		b = uf.find_set(b);
 
		sum += 1LL * uf.len[a] * uf.len[b] * x;
 
		uf.join(a, b);
	}
 
	cout << sum << '\n';
 
	return 0;
}
