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

const int N = 5e5 + 10, K = 19;

int sp[K][N];

void buildSparse(vector<int>& a) {
  int n = a.size();
  int l = 32 - __builtin_clz(n);
  
  for(int i = 0; i < n; ++i) sp[0][i]  = a[i];
  for(int i = 1; i < l; ++i)
    for(int j = 0; j + (1 << i) <= n; ++j)
      sp[i][j] = max(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]); 
}

int query(int l, int r) {
  int lg = 31 - __builtin_clz(r - l + 1);
  return max(sp[lg][l], sp[lg][r - (1 << lg) + 1]);
}

i64 mega_query(vector<int>& a) {
  int n = a.size();
  vector<int> lo(n), hi(n);
  vector<ii> st;
  st.pb({INF + 1, -1});
  for(int i = 0; i < n; ++i) {
    while(!st.empty() && st.back().fi <= a[i]) st.pop_back();
    lo[i] = st.back().sc + 1;
    st.emplace_back(a[i], i);
  }  
  st.clear();
  st.pb({INF + 1, n});
  for(int i = n - 1; i >= 0; --i) {
    while(!st.empty() && st.back().fi < a[i]) st.pop_back();
    hi[i] = st.back().sc - 1;
    st.emplace_back(a[i], i);
  }
  i64 ans = 0;
  for(int i = 0; i < n; ++i)
    ans += a[i] * (i - lo[i] + 1ll) * (hi[i] - i + 1ll);
  return ans;
}

void solve() {
    int n, q;
    cin >> n;
    vector<int> a(n);
    for(int& v : a) cin >> v;
    buildSparse(a);
    cin >> q;
    while(q--) {
      int m;
      i64 ans = 0;
      cin >> m;
      vector<int> ind(m), b;
      for(int& v : ind) {cin >> v; --v; ans += a[v];}
      for(int i = 0; i < m - 1; ++i) b.pb(query(ind[i], ind[i + 1]));
      ans += mega_query(b);
      cout << ans << '\n';
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
