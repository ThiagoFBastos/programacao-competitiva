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

void solve() {
  int q;
  cin >> q;
  vector<i64> a(q, 0);
  ordered_set<pair<i64, int>> os;
  for(int i = 0; i < q; ++i) {
    int t;
    cin >> t;
    if(t == 1) {
      int v;
      cin >> v;
      a[i] = v;
      os.insert(make_pair(v, i));
    } else if(t == 2) {
      int k;
      cin >> k;
      --k;
      os.erase(make_pair(a[k], k));
    } else if(t == 3) {
      int k, v;
      cin >> k >> v;
      --k;
      os.erase(make_pair(a[k], k));
      a[k] += v;
      os.insert(make_pair(a[k], k)); 
    } else {
      int k;
      cin >> k;
      --k;
      cout << os.order_of_key(make_pair(a[k], -1)) << '\n'; 
    }
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
