#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

struct uf {
	vector<int> par, rank, sz;

	uf() {}

	uf(int n) {
		par.resize(n);
		rank.assign(n, 0);
		sz.assign(n, 1);
		iota(par.begin(), par.end(), 0);
	}
	
	int findSet(int v) {
		return v == par[v] ? v : par[v] = findSet(par[v]);
	}

	bool same(int a, int b) {
		return findSet(a) == findSet(b);
	}
	
	bool join(int a, int b) {
		a = findSet(a);
		b = findSet(b);

		if(a == b) return false;
		else if(rank[a] > rank[b]) swap(a, b);
		
		par[a] = b;
		rank[b] += rank[a] == rank[b];
		sz[b] += sz[a];

		return true;
	}
};

void solve() {
	int n;

	cin >> n;

	vector<int> a(n);
	set<int> st;
	bool eq = true;
	uf dsu(n + 1);

	for(int& v : a) cin >> v;

	for(int i = 1; i <= n; ++i) st.insert(i);
	
	for(int i = 1; i < n; ++i) {
		int u = -1;
		if(eq && !dsu.same(i, a[i - 1]) && st.count(a[i - 1])) u = a[i - 1];
		else {
			for(int v : st) {
				if(!dsu.same(i, v)) {
					u = v;
					break;
				}
			}
		}		
		cout << u << ' ';		
		eq = eq && a[i - 1] == u;
		dsu.join(u, i);
		st.erase(u);
	}

	cout << *st.begin() << '\n';
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

