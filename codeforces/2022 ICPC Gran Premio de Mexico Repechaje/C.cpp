#include "bits/stdc++.h"

using namespace std;
 
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
	int n, m;
  i64 sum = 0;
  cin >> n >> m;
  map<int, int, greater<int>> mp;
  for(int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    ++mp[a];
    sum += a;
  }
  while(m--) {
    int q;
    cin >> q;
    while(mp.begin()->fi > q) {
      ii x = *mp.begin();
      mp.erase(mp.begin());
      sum -= (i64)x.fi * x.sc;
      sum += (i64)q * x.sc;
      mp[q] += x.sc;
    }
    cout << sum <<'\n';
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
