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

const int N = 1e3 + 10;

int a[N][N];

void solve() {
  int n;
  
  cin >> n;
  
  using T = tuple<int, int, int>;
  set<T, greater<T>> st;
  
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
        cin >> a[i][j];
        if(i < j) st.emplace(a[i][j], i, j);
    }
  }
  
  i64 ans = 0;
  vector<ii> couple;
  vector<bool> alive(n, true);
  
  while(!st.empty()) {
    auto [p, i, j] = *st.begin();
    
    st.erase(st.begin());
    
    if(i > j) swap(i, j);
    
    couple.pb({i+1, j+1});
    ans += p;
    
    for(int k = 0; k < n; ++k) {
      if(!alive[k]) continue;
      st.erase(make_tuple(a[i][k], min(i,k), max(i,k)));
      st.erase(make_tuple(a[j][k], min(j,k), max(j,k)));
    }
    
    alive[j] = false;
    
    for(int k = 0; k < n; ++k) {
      if(!alive[k]) continue;
      a[k][i] = a[i][k] = max(a[i][k], a[j][k]);
      if(k == i) continue;
      st.emplace(a[i][k], min(i, k), max(i, k));
    }
  }
  
  cout << ans << '\n';
  for(auto [i, j] : couple) cout << i << ' ' << j << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}


