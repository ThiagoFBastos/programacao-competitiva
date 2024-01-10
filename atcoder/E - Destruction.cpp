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
	int n, m;
	cin >> n >> m;

	DSU dsu(n);
	vector<tuple<int, int, int>> e;
	i64 ans = 0;

	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		if(c <= 0) dsu.join(a, b);
		else {
			e.emplace_back(c, a, b);
			ans += c;
		}
	}

	sort(e.begin(), e.end());

	for(auto [c, a, b] : e) {
		if(!dsu.join(a, b)) continue;
		ans -= c;		
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
