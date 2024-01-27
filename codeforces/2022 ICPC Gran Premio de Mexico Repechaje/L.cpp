#include "bits/stdc++.h"
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>


using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, 
tree_order_statistics_node_update>;
 
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

void solve() {
   int n, x;
  
   cin >> n >> x;
   
   --x;
   
   vector<vector<int>> adj(n);
   vector<int> depth(n, 0), sz(n), par(n);
   
   for(int i = 1; i < n; ++i) {
     int a, b;
     cin >> a >> b;
     --a, --b;
     adj[a].pb(b); adj[b].pb(a);
   }
   
   auto dfs = [&](auto& self, int u, int p)->void {
     sz[u] = 1;
     par[u] = p;
     for(int v : adj[u]) {
       if(v == p) continue;
       depth[v] = 1 + depth[u];
       self(self, v, u);
       sz[u] += sz[v];
     }
   };
   
   dfs(dfs, 0, -1);
 
   int ans = 2 * (n - 1) - depth[par[x]];
   ans -= 2 * (sz[par[x]] - 1);
   ++ans;
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
