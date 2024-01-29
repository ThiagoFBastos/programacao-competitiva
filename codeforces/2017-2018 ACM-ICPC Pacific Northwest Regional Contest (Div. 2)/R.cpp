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

#define INF 0x3f3f3f3f
#define MAX 1000000

void solve() {
  int n;
  double x,v;
  cin >> n >> x >> v;
  
  double l, r, vi;
  double vy = 0.0;
  
  for(int i=0; i<n; i++)
  {
    cin >> l >> r >> vi;
    vy += (r-l)*vi;
  }
  
  vy = vy / x;
  
  // v2 = vx2 + vy2
  // vx = sqrt ( v2 - vy2 )
  double vx = sqrt(v*v - vy*vy);
  
  // v = s / t
  // t = s / v
  double tempo = x / vx;
  
  if(abs(vy) > v)
    cout << "Too hard\n";
  
  else
    printf("%.3f\n", tempo);

}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
