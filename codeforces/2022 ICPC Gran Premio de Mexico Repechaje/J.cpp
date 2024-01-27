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
  int n;
  
  cin >> n;
  
  vector<vector<int>> adj(n);
  vector<int> b(n);
  vector<array<i64, 2>> dp(n);
  
  for(int& v : b) cin >> v;
  
  for(int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    adj[a].pb(b); adj[b].pb(a); 
  }      
  
  auto dfs = [&](auto& self, int u, int p)->void {
      vector<i64> swaps;
      i64 tot = 0;
      int deg = adj[u].size() - (p != -1);
      
      for(int v : adj[u]) {
        if(v == p) continue;
        self(self, v, u);
        tot += dp[v][0];
        swaps.pb(dp[v][1] - dp[v][0]);
      }
      
      sort(rall(swaps));
      
      vector<i64> ps(deg + 1);
      
      ps[0] = 0;
      for(int i = 1; i <= deg; ++i) ps[i] = ps[i - 1] + swaps[i - 1];
      
      dp[u][0] = tot + b[deg];
      dp[u][1] = tot + b[deg + (u != p)];
      
      for(int i = 0; i < deg; ++i)
        dp[u][0] = max(dp[u][0], tot + ps[deg - i] + b[i]);
        
      if(p != -1) {
        for(int i = 1; i <= deg; ++i)
          dp[u][1] = max(dp[u][1], tot + ps[deg - i + 1] + b[i]);
      }
  };
  
  dfs(dfs, 0, -1);
  cout << dp[0][0] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
