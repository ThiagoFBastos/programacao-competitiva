#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
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
const int maxn = 1e4;
vi Gin[maxn], Gout[maxn];
int n, m, a, b, d[maxn], cs[maxn];
int dist(int src, int dest) {
	priority_queue<ii, vii, greater<ii>> pq;	
	for(int v = 0; v < n; ++v) {
		cs[v] = INT_MAX;
		d[v] = -1;
	}
	pq.push({0, src});
	while(!pq.empty()) {
		auto [c, v] = pq.top();	
		pq.pop();
		if(d[v] != -1) continue;
		d[v] = c;
		for(int u : Gout[v])
			if(d[u] == -1 && cs[u] > c) {
				cs[u] = c;
				pq.push({c, u});
			}
		for(int u : Gin[v]) {
			if(d[u] == -1 && cs[u] > c + 1) {
				cs[u] = c + 1;
				pq.push({c + 1, u});
			}
		}
	}
	return d[dest] == -1 ? INT_MAX : d[dest];	
}
void solve() {
	int X, Y;
	X = dist(a, b);
	Y = dist(b, a);
	if(X < Y) cout << "Bibi: " << X << '\n';
	else if(X > Y) cout << "Bibika: " << Y << '\n';
	else cout << "Bibibibika\n";
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);	
	cin >> n >> m >> a >> b;
	--a, --b;
	for(int k = 0; k < m; ++k) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		Gout[u].push_back(v);
		Gin[v].push_back(u);
	}
	solve();
 	return 0;
}