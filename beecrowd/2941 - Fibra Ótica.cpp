#pragma GCC target("sse,mmx,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;
struct edge {
	int a, b, w;
};
struct disjointSet {
	vi rank, pai;
	disjointSet(int n) {
		rank.assign(n, 0);
		pai.resize(n);
		for(int v = 0; v < n; ++v) pai[v] = v;
	}
	int findSet(int v) {
		return v == pai[v] ? v : pai[v] = findSet(pai[v]);
	}
	void join(int a, int b) {
		if(a == b) return;
		else if(rank[a] < rank[b]) pai[a] = b;
		else {
			pai[b] = a;
			if(rank[a] == rank[b]) ++rank[a];
		}
	}
};
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, c[450][450], c1 = 0, c2 = 0;	
	cin >> n;
	vector<edge> e1, e2;
	for(int k = 0; k < n; ++k) {
		for(int i = 0; i < n; ++i) {
			cin >> c[k][i];
			if(k <= i) continue;
			else if(c[k][i]) {
				e1.push_back({k, i, c[i][k]});
				c1 += c[i][k];
			}
			else
				e2.push_back({k, i, c[i][k]});
		}
	}
	sort(e1.begin(), e1.end(), [](edge e1, edge e2) {
		return e1.w > e2.w;
	});
	sort(e2.begin(), e2.end(), [](edge e1, edge e2) {
		return e1.w < e2.w;
	});
	disjointSet p(n);
	for(auto [a, b, w] : e1) {
		int u = p.findSet(a), v = p.findSet(b);
		if(u == v) continue;
		p.join(u, v);
		c1 -= w;
	}
	c2 += c1;
	for(auto [a, b, w] : e2) {
		int u = p.findSet(a), v = p.findSet(b);
		if(u == v) continue;
		p.join(u, v);
		c2 += w;
	}
	cout << c2 << '\n';
	return 0;
}