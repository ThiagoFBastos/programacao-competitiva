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

bool fn(int a, int b, string t, int c) {
  //"=", "!=", "<", ">", "<=" or ">=",
  if(t == "=") return a + b == c;
  else if(t == "!=") return a + b != c;
  else if(t == "<") return a + b < c;
  else if(t == ">") return a + b > c;
  else if(t == "<=") return a + b <= c;
  return a + b >= c;
}

void solve() {
  int n, m;
  
  cin >> n >> m;
  
  vector<vector<int>> adj(2 * n);
  vector<int> low(2 * n), in(2 * n, -1), scc(2 * n, -1), st;
  int t = 0, id = 0;
  
  auto add = [&](int p, int sp, int q, int sq) {
    adj[2 * p + (sp ^ 1)].pb(2 * q + sq);
    adj[2 * q + (sq ^ 1)].pb(2 * p + sp);
  };
  
  for(int i = 0; i < m; ++i) {
      int x, y, z;
      string t;
      cin >> x >> y >> t >> z;
      for(int a : {0, 1}) {
        for(int b : {0, 1}) {
          if(!fn(a, b, t, z))
            add(x, a ^ 1, y, b ^ 1);
        }
      }
  }
  
  auto dfs = [&](auto& self, int u)->void {
    low[u] = in[u] = t++;
    st.pb(u);
    for(int v : adj[u]) {
      if(in[v] < 0) {
        self(self, v);
        low[u] = min(low[u], low[v]);
      } else if(scc[v] < 0)
        low[u] = min(low[u], low[v]);
    }
    if(low[u] != in[u]) return;
    while(true) {
      int v = st.back(); st.pop_back();
      scc[v] = id;
      if(u == v) break;
    }
    ++id;
  };
  
  for(int i = 0; i < 2 * n; ++i) if(in[i] < 0) dfs(dfs, i);
  
  for(int i = 0; i < n; ++i) {
    if(scc[2 * i] == scc[2 * i + 1]) {
      cout << "No\n";
      return;
    }
  }
  
  cout << "Yes\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
