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
	int n, m;
  
  cin >> n >> m;
  
  vector<int> a(n);
  set<ii, greater<ii>> pq;
  
  for(int i = 0; i < n; ++i) {
    cin >> a[i];
    pq.emplace(a[i], i);
  }
  
  while(!pq.empty()) {
    auto [x, i] = *pq.begin();
    
    pq.erase(pq.begin());
    
    if(i > 0 && abs(a[i - 1] - a[i]) > m) {
      pq.erase(ii(a[i - 1], i - 1));
      a[i - 1] = a[i] - m;
      pq.emplace(a[i - 1], i - 1);
    }
    
    if(i + 1 < n && abs(a[i + 1] - a[i]) > m) {
      pq.erase(ii(a[i + 1], i + 1));
      a[i + 1] = a[i] - m;
      pq.emplace(a[i + 1], i + 1);
    }
  }
  
  for(int v : a) cout << v << ' ';
  cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}


