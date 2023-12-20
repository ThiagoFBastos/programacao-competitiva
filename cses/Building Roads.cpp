#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
class disjoint_set {
	vi rank, pa;
	int n;
	public:
	disjoint_set(int n) {
		this->n = n;
		rank.resize(n);
		pa.resize(n);
		for(int v = 0; v < n; ++v) rank[v] = 0, pa[v] = v;
	}
	void join(int v, int w) {
		v = find_set(v);
		w = find_set(w);
		if(v != w) {
			--n;
			if(rank[v] < rank[w])
				pa[v] = w;
			else {
				pa[w] = v;
				if(rank[v] == rank[w]) ++rank[v];
			}
		}
	}
	int find_set(int v) {
		return v == pa[v] ? v : pa[v] = find_set(pa[v]); 
	}
	int set_size() const {
		return n;
	}
};
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	disjoint_set s(n);
	while(m--) {
		int u, v;
		cin >> u >> v;
		s.join(u - 1, v - 1);
	}
	vi V;
	cout << s.set_size() - 1 << '\n';
	for(int v = 0; v < n; ++v) {
		if(v == s.find_set(v))
			V.push_back(v);
	}
	for(int v = 1; v < V.size(); ++v)
		cout << V[v - 1] + 1 << ' ' << V[v] + 1 << '\n';
    return 0;
}
