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
	
	int n, q;

	cin >> n >> q;
	
	DSU dsu(n);
	vector<unordered_map<int, int>> groups(n);

	for(int i = 0; i < n; ++i) {
		int c;
		cin >> c;
		++groups[i][c];
	}

	while(q--) {
		int t, a, b;
		cin >> t >> a >> b;

		if(t == 1) {
			--a, --b;
			int u = dsu.findSet(a);
			int v = dsu.findSet(b);

			if(dsu.join(u, v)) {
				int x = dsu.findSet(u);
				int y = u ^ v ^ x;			
				if(groups[x].size() < groups[y].size()) swap(groups[x], groups[y]);
				for(auto [p, q] : groups[y]) groups[x][p] += q;
			}

		} else {
			int u = dsu.findSet(a - 1);
			auto it = groups[u].find(b);
			if(it == groups[u].end()) cout << "0\n";
			else cout << it->second << '\n';
		}
	}
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
