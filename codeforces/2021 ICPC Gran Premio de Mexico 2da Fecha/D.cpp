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
  int c,r,s;
  cin >> c >> r >> s;
  
  int total = c+r;

  int CT = total/s;
  if(total%s > 0)
    CT++;
    
  int CP = r/s;
  if(r%s > 0)
    CP++;
  
  int maximo = CT - CP;
  int minimo = max(CT-r,0);
  
  cout << maximo << " " << minimo << "\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}
