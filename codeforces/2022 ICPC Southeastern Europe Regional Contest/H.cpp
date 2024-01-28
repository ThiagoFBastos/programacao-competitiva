#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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
  
  vector<int> p(n);
  vector<ii> op;
  
  for(int& v : p) cin >> v;
    
  reverse(all(p));
  
  int cur = 1;
  
  for(int i = 1; i < n; ++i) {
    
      while(cur < n && p[cur] < p[cur - 1]) ++cur;
      
      if(cur == n) break;
      
      vector<int> aux;
      int lo = cur, y = p[cur];
      
      for(int j = 0; j < cur; ++j) {
         op.emplace_back(1, 2);
         aux.pb(p[j]);       
      }
      
      reverse(all(aux));
      
      op.emplace_back(1, 3);
      
      for(int x : aux) {
          if(x > y) break;
          op.emplace_back(2, 1);
          p[lo--] = x;
      }
      
      p[lo--] = y;
      op.emplace_back(3, 1);
      
      for(int x : aux) {
            if(x < y) continue;
            op.emplace_back(2, 1);
            p[lo--] = x;
      }
  }
  
  for(int x : p) op.emplace_back(1, 3);
  
  cout << size(op) << '\n';
  
  for(auto [a, b] : op) cout << a << ' ' << b << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}


