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
  string s, t;
  
  cin >> s >> t;
  
  vector<int> pos[26];
  
  int n = s.size();
  
  for(int i = 0; i < n; ++i) pos[s[i] - 'a'].pb(i);
  
  int cur = 0, days = 1;
  
  for(char c : t) {
    auto& P = pos[c - 'a'];
    if(P.back() < cur) cur = 0, ++days;
    cur = *lower_bound(all(P), cur);
    ++cur;
  }
  
  cout << days << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}


