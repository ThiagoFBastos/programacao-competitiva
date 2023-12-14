#include "bits/stdc++.h"
 
using namespace std;
 
#define INF    1000000000
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
 
const int N = 1e5 + 10, K = 17;
 
vector<int> adj[N];
int full_sub[N], depth[N], in[N], sub[N], n, q, t;
int sp[K][N];
bool full[N];
set<ii> st;
 
void dfslifting(int u, int p) {
	sp[0][u] = p;
	for(int i = 1; (1 << i) <= n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	sub[u] = u;
	for(int v : adj[u]) {
		depth[v] = 1 + depth[u];
		dfslifting(v, u);
		sub[u] = min(sub[u], sub[v]);
	}
	sort(all(adj[u]), [&](int a, int b) {
		return sub[a] < sub[b];
	});
}
 
void dfsorder(int u, int p) {
	in[u] = t++;
	for(int v : adj[u]) dfsorder(v, u);
}
 
int add(int k) {
	int last = -1;
	for(int i = 0; i < k; ++i) {
		auto [_, u] = *st.begin();
		last = u + 1;
		full[u] = true;
		st.erase(st.begin());
		int p = sp[0][u];
		if(p != u && ++full_sub[p] == (int)adj[p].size()) st.emplace(in[p], p);
	}
	return last;
}
 
int rem(int v) {
	int u = v, d = depth[v];
 
	for(int i = 31 - __builtin_clz(n); i >= 0; --i) {
		if(d - (1 << i) < 0) continue;	
		int p = sp[i][u];
		if(!full[p]) continue;
		u = p, d -= 1 << i;
	}
 
	int p = sp[0][u];
 
	if(p != u && full_sub[p]-- == (int)adj[p].size()) st.erase(ii(in[p], p));
	
	full[u] = false;
	st.emplace(in[u], u);
	
	return depth[v] - depth[u];
}
 
void solve() {
 
	cin >> n >> q;
 
	int r = -1;
 
	for(int i = 0; i < n; ++i) {
		int p;
		cin >> p;
		--p;
		if(p >= 0) adj[p].pb(i);
		else r = i;
	}
	
	dfslifting(r, r);
	dfsorder(r, r);
 
	for(int i = 0; i < n; ++i) if(adj[i].empty()) st.emplace(in[i], i);
 
	while(q--) {
		int t, v;
		cin >> t >> v;
		if(t == 1) cout << add(v) << '\n';
		else cout << rem(v - 1) << '\n';
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
