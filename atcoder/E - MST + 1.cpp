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

struct DSU {
	vector<int> pai, rank, sz;
	
	DSU(int n) {
		pai.resize(n);
		rank.assign(n, 0);
		sz.assign(n, 1);
		iota(pai.begin(), pai.end(), 0);
	}
	
	int findSet(int v) {
		return v == pai[v] ? v : pai[v] = findSet(pai[v]);
	}

	bool same(int a, int b) {
		return findSet(a) == findSet(b);
	}
	
	bool join(int a, int b) {
		a = findSet(a);
		b = findSet(b);
		if(a == b) return false;
		else if(rank[a] > rank[b]) swap(a, b);
		pai[a] = b;
		rank[b] += rank[a] == rank[b];
		sz[b] += sz[a];
		return true;
	}
};

void solve() {

	int n, m, q;

	cin >> n >> m >> q;	

	vector<tuple<int, int, int>> edge(m);
	vector<tuple<int, int, int, int>> queries(q);
	vector<bool> ans(q, false);
	DSU dsu(n);

	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		edge[i] = {c, a, b};
	}

	sort(edge.begin(), edge.end());
	
	for(int i = 0; i < q; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		queries[i] = {c, a, b, i};
	}

	sort(queries.begin(), queries.end());

	int i = 0, j = 0;

	while(j < q && i < m) {
		auto [w1, a1, b1] = edge[i];
		auto [w2, a2, b2, k] = queries[j];
		if(w1 < w2) dsu.join(a1, b1), ++i;
		else {
			if(!dsu.same(a2, b2)) ans[k] = true;
			++j;
		}
	}

	while(j < q) {
		auto [w2, a2, b2, k] = queries[j++];
		if(!dsu.same(a2, b2)) ans[k] = true;
	}

	for(bool v : ans) if(v) cout << "Yes\n"; else cout << "No\n";
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
