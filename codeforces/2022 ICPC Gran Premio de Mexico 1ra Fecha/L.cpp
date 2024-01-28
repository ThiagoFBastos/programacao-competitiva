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

const int N = 1e6 + 100, MOD = 1e9 + 7;

i64 pre[N];

void solve() {

      int n;
      
      cin >> n;
      
      vector<int> a(n + 1), lo(n + 1), hi(n + 1);
      vector<ii> st;
      
      st.emplace_back(INF + 1, 0);
      
      for(int i = 1; i <= n; ++i) {
          cin >> a[i];
          
          pre[i] = a[i] + pre[i - 1];
          
          while(!st.empty() && st.back().fi <= a[i]) st.pop_back();
          
          lo[i] = 1 + st.back().sc;
          
          st.emplace_back(a[i], i);
      }
      
      st.clear();
      st.emplace_back(INF + 1, n + 1);
      
      for(int i = n; i; --i) {
          while(!st.empty() && st.back().fi <= a[i]) st.pop_back();
          hi[i] = st.back().sc - 1;
          st.emplace_back(a[i], i);
      }
      
      for(int i = 1; i <= n; ++i)
          pre[i] = (pre[i] + pre[i - 1]) % MOD;
      
      i64 ans = 0;
      
      for(int i = 1; i <= n; ++i) {
          
          i64 l = -(pre[i - 1] - pre[max(0, lo[i] - 2)]) % MOD;
          i64 r = (pre[hi[i]] - pre[i - 1]) % MOD;
          
          ans = (ans + l * (hi[i] - i + 1)) % MOD;
          ans = (ans + r * (i - lo[i] + 1)) % MOD;
      }
      
      ans = (ans + MOD) % MOD;
      
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


