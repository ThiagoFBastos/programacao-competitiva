#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
class disjoint_set {
	vi rank, p, s;
	public:
	disjoint_set(int n) {
		rank.resize(n);
		p.resize(n);
		s.resize(n);
		for(int v = 0; v < n; ++v) {
			rank[v] = 0;
			s[v] = 1;
			p[v] = v;
		}
	}
	int find_set(int v) {
		return v == p[v] ? v : p[v] = find_set(p[v]);
	}
	void join(int u, int v) {
		if(rank[u] < rank[v]) {
			p[u] = v;
			s[v] += s[u];
		}
		else {
			p[v] = u;
			s[u] += s[v];
			if(rank[u] == rank[v]) ++rank[u];
		}
	}
	int group_size(int v) {
		return s[v];
	}
};
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<tuple<int, int, int>> roads(m);
	disjoint_set s(n);
	for(auto &[c, u, v] : roads) {
		cin >> u >> v >> c;
		--u, --v;
	}
	sort(roads.begin(), roads.end());
	ll cost = 0;
	for(auto [c, u, v] : roads) {
		int a = s.find_set(u), b = s.find_set(v);
		if(a != b) {
			cost += c;
			s.join(a, b);
		}
	}
	for(int v = 0; v < n; ++v) {
		if(s.group_size(v) == n) {
			cout << cost << '\n';
			return 0;
		}
	}
	cout << "IMPOSSIBLE\n";
	return 0;
}
