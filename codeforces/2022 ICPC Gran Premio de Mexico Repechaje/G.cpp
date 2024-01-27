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
    int n, q;
    
    cin >> n >> q;
    
    vector<int> c1 = {0, 1, 2, 3};
    vector<int> c2 = {0, 1, 2, 3, 4, 5, 6, 7};
    
    /*
          x     x
        
        x         x
        
        x         x
        
          x     x
    */
    
    vector<int> c3 = {0, 1, 2, 3};
    
  
    /*
              x
          x      x
              x
    */
        
        
    auto applyc1 = [&](char t) {
      if(t == 'a') {
        swap(c1[0], c1[1]);
        swap(c1[2], c1[3]);
      } else if(t == 'b') {
        swap(c1[1], c1[2]);
      } else if(t == 'c') {
        swap(c1[0], c1[2]);
        swap(c1[1], c1[3]);  
      } else {
        swap(c1[0], c1[3]);
      }
    };
    
    
    /*
          x     x
        
        x         x
        
        x         x
        
          x     x
    */
    
    
    auto applyc2 = [&](char t) {
       if(t == 'a') {
         swap(c2[0], c2[2]);
         swap(c2[1], c2[4]);
         swap(c2[3], c2[6]);
         swap(c2[5], c2[7]);
      } else if(t == 'b') {
        swap(c2[0], c2[1]);
        swap(c2[2], c2[3]);
        swap(c2[4], c2[5]);
        swap(c2[6], c2[7]);
      } else if(t == 'c') {
        swap(c2[0], c2[5]);
        swap(c2[1], c2[3]);
        swap(c2[2], c2[7]);
        swap(c2[4], c2[6]);
      } else {
          swap(c2[0], c2[6]);
          swap(c2[1], c2[7]);
          swap(c2[2], c2[4]);
          swap(c2[3], c2[5]); 
      }
    };
    
      /*
        x   x
        
        x   x
    */
    
    
    auto applyc3 = [&](char t) {
      if(t == 'a') {
        swap(c3[1], c3[2]);
      } else if(t == 'b') {
        swap(c3[0], c3[1]);
        swap(c3[2], c3[3]);
      } else if(t == 'c') {
        swap(c3[0], c3[3]);
      } else {
        swap(c3[0], c3[2]);
        swap(c3[1], c3[3]); 
      }
    };
    
    auto findC = [&](int i, int j) {
        vector<ii> c;
        int x = i, y = j;
        for(int k : {0, 1}) {
          c.pb({i, j});
          c.pb({n - i - 1, j});
          c.pb({n - i - 1, n - j - 1});
          c.pb({i, n - j - 1});
          swap(i, j);
        }
        sort(all(c));
        c.resize(unique(all(c)) - c.begin());
        vector<int> my_cycle;
        if((int)c.size() == 8) my_cycle = c2;
        else if(n % 2 && (i == n / 2 || j == n / 2)) my_cycle = c1;
        else my_cycle = c3;
        int k = find(all(c), ii(x,y)) - c.begin();
        auto [xt, yt] = c[my_cycle[k]];
        return (i64)xt * n + yt + 1;
    };
    
    while(q--) {
      char t;
      cin >> t;
      if(t == 'r') {
        char d;
        cin >> d;
        applyc1(d);
        applyc2(d);
        applyc3(d);
      } else {
        int x, y;
        cin >> x >> y;
        cout << findC(x-1, y-1) << '\n';
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
