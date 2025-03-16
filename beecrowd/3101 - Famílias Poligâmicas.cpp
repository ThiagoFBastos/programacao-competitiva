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
	int n, m, k;
	cin >> n >> m;
	
	DSU dsu(n);
	vector<bool> alive(n, true);
	vector<ii> edge;
	
	while(m--) {
		int a, b;
		cin >> a >> b;
		dsu.join(a - 1, b - 1);
	}
	
	cin >> k;
	
	while(k--) {
		int id;
		cin >> id;
		--id;
		if(alive[id]) {
			--dsu.sz[dsu.findSet(id)];
			alive[id] = false;
		}
	}
	
	vector<int> S;
	
	for(int v = 0; v < n; ++v) {
		if(v != dsu.findSet(v) || !dsu.sz[v]) continue;
		S.push_back(dsu.sz[v]);
	}
	
	sort(S.begin(), S.end());
	
	cout << "Quantidade de familias: " << size(S) << '\n';
	cout << "Numero de habitantes em cada: ";
	
	cout << S[0];
	for(int i = 1; i < (int)S.size(); ++i) {
		if(i < (int)S.size() - 1) cout << ", ";
		else cout << " e ";
		cout << S[i];
	}
	
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}