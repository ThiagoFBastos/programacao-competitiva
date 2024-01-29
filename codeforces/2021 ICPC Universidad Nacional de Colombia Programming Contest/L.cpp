#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int N = 1e6 + 100;

int n, q, weight[N];
bitset<N> dp;
vector<int> a;
vector<vector<int>> g;

int dfs(int u, int p) {
  int x = 0;
  
  for(int v : g[u]) {
     if(v == p) continue;
     int y = dfs(v, u);
     if(y < 0) return -1;
     x = max(x, y);
  }
  
  if(x > a[u]) {
   if(x - a[u] >= N || weight[x - a[u]] == -1) return -1; 
   a[u] += weight[x - a[u]]; 
  }
  
  return max(x, a[u]);
}

void solve() {

   cin >> n >> q;
   
   dp[0] = 1;
   
   a.resize(n);
   g.resize(n);
   
   for(int i = 0; i < n; ++i) cin >> a[i];
   
   for(int i = 1; i < n; ++i) {
     int u, v;
     cin >> u >> v;
     --u, --v;
     g[u].push_back(v);
     g[v].push_back(u);
   }
   
   while(q--) {
     int x;
     cin >> x;
     dp |= dp << x;
   }
  

   for(int k = N - 1, X = -1; k >= 0; --k) {
     if(dp[k]) X = k;
     weight[k] = X;
   }
   
   if(dfs(0, 0) < 0) {
     cout << "-1\n";
     return;
   }
   
   cout << accumulate(a.begin(), a.end(), 0LL) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

