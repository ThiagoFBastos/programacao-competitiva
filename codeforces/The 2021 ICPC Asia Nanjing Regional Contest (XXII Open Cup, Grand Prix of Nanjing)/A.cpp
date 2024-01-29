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
  int n, a, b;
  cin >> n >> a >> b;
  
  char lr = 'L', ud = 'U';
  int posLR = 1;
  int posUD = 1;
  
  if(a>n/2)
  {
    ud = 'D';
    posUD = n;
  }
    
  if(b>n/2)
  {
    lr = 'R';  
    posLR = n;
  }
  
  for(int i=0; i<n-1; i++)
    cout << ud << lr;
  
  if(ud == 'D')
    ud = 'U';
  else
    ud = 'D';
  
  if(lr == 'L')
    lr = 'R';
  else
    lr = 'L';
  
  for(int i=0; i<abs(a-posUD); i++)
    cout << ud;
  
  for(int i=0; i<abs(b-posLR); i++)
    cout << lr;
  
  cout << "\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	// cin >> t;
	while(t--) solve();
 	return 0;
}

