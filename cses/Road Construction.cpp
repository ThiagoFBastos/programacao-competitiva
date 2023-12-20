#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
#define f first
#define s second
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
class disjoint_set {
	vi rank, p, set_size;
	public:
	disjoint_set(int n) {
		rank.resize(n);
		p.resize(n);
		set_size.resize(n);
		for(int v = 0; v < n; ++v) {
			set_size[v] = 1;
			rank[v] = 0;
			p[v] = v;
		}
	}
	int join(int u, int v) {
		if(rank[u] < rank[v]) {
			p[u] = v;
			set_size[v] += set_size[u];
			return set_size[v];
		}
		p[v] = u;
		set_size[u] += set_size[v];
		return set_size[u];
	}
 
	int find_set(int v) {
		return v == p[v] ? v : p[v] = find_set(p[v]);
	}
};
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	disjoint_set s(n);
	int max_cc = 1, cc = n;
	for(int k = 0; k < m; ++k) {
		int u, v;
		cin >> u >> v;
		u = s.find_set(u - 1);
		v = s.find_set(v - 1);
		if(u != v) {
			--cc;
			max_cc = max(max_cc, s.join(u, v));
		}
		cout << cc << ' ' << max_cc << '\n';
	}
	return 0;
} 
