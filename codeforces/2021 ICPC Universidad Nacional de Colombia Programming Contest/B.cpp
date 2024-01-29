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

void solve() {
  int n, m;
  cin >> n >> m;
  
  if(cin.eof()) exit(0);
  
  i64 h = 1;
  
  for(int i=0; i<m; i++)
  {
    int w,u,v;
    cin >> w >> u >> v;
    
    if(w%2==1)
      h*=w;
  }
  
  cout << h << "\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	// cin >> t;
	while(1) solve();
 	return 0;
}


