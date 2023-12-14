#include "race.h"
#include <vector>
#include <set>
#include <utility>
#include <functional>
 
using namespace std;
 
using ii = pair<int, int>;
using i64 = long long;
 
int best_path(int N, int K, int H[][2], int L[])
{	
  vector<vector<ii>> g(N);ss
  vector<i64> pre(N);
  vector<set<pair<i64, int>>> S(N);
  int ans = N + 1;
  
  for(int i = 0; i < N - 1; ++i) {
  	int u = H[i][0], v = H[i][1];
  	g[u].emplace_back(v, L[i]);
  	g[v].emplace_back(u, L[i]);
  }
  
  pre[0] = 0;
  
  function<void(int, int, int)> dfs = [&](int u, int p, int h) {
  	
  	S[u].insert(make_pair(pre[u], h));
  	
  	for(auto [v, w] : g[u]) {
  		if(v == p) continue;
  		
  		pre[v] = pre[u] + w;
  		dfs(v, u, h + 1);
  		
  		if(S[v].size() > S[u].size()) swap(S[u], S[v]);
  		
  		for(auto [cost, depth] : S[v]) {
  			i64 X = K - cost + 2 * pre[u];
  			auto k = S[u].lower_bound(make_pair(X, -1));
  			if(k == S[u].end() || k->first != X) continue;
  			ans = min(ans, depth + k->second - 2 * h);
  		}
  		
  		for(auto [cost, depth] : S[v]) S[u].insert(make_pair(cost, depth));
  	}
  };
  
  dfs(0, 0, 0);
  
  if(ans == N + 1) ans = -1;
  
  return ans;
}
