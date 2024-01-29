#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

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

const int N = 2e5 + 10;

vector<int> adj[N];

int a[N], n, maxv[N], sz[N];
i64 cost[N], pairs;

int findCentroid(int n, int u) {
	int p = -1;
	while(true) {
		ii heavy(-1, -1);
		for(int v : adj[u]) if(v != p) heavy = max(heavy, ii(sz[v], v));
		if(max(n - sz[u], heavy.fi) <= n / 2) break;
		p = u, u = heavy.sc;
	}
	return u;
}

void dfssize(int u, int p) {
	sz[u] = 1;
	for(int v : adj[u]) {
		if(v == p) continue;
		dfssize(v, u);
		sz[u] += sz[v];
	}
}

void dfsquery(vector<pair<int, i64>>& A, int u, int p) {
	cost[u] += a[u];
	maxv[u] = max(maxv[u], a[u]);
	A.pb({maxv[u], cost[u]});
	for(int v : adj[u]) {
		if(v == p) continue;
		cost[v] = cost[u], maxv[v] = maxv[u];
		dfsquery(A, v, u);
	}
}

vector<pair<int, i64>> A;
ordered_set<pair<i64, int>> os;

void build(int u, int p) {
	for(int& v : adj[u]) if(v == p) swap(v, adj[u].back());

	if(p != -1) adj[u].pop_back();

	dfssize(u, -1);
	
	int c = findCentroid(sz[u], u);

	A.clear();

	for(int v : adj[c]) {
		int L = A.size();
		cost[v] = maxv[v] = a[c];
		dfsquery(A, v, c);
		sort(A.begin() + L, A.end());
		os.clear();
		for(int i = L; i < (int)A.size(); ++i) {
			pairs -= (int)os.size() - (int)os.order_of_key(make_pair(2*A[i].fi-A[i].sc + a[c],INF));
			os.insert(make_pair(A[i].sc, i));
		}
	}
	
	sort(all(A));
	os.clear();

	for(int i = 0; i < (int)A.size(); ++i) {
		pairs += (int)os.size() - (int)os.order_of_key(make_pair(2*A[i].fi - A[i].sc + a[c],INF));
		pairs += A[i].sc - 2 * A[i].fi > 0;	
		os.insert(make_pair(A[i].sc, i));
	}

	for(int v : adj[c]) build(v, c);
}

void solve() {
	cin >> n;

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		adj[i].clear();
	}

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	pairs = 0;
	build(0, -1);

	cout << pairs << '\n';		
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

