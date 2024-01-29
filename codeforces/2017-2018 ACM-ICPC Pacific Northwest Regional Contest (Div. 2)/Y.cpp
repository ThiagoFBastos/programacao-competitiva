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
  double k,p,x;
  cin >> k >> p >> x;
  
  double ans = INF;
  
  for(int m=1; m<=MAX; m++)
  {
    double days = k / (m * 1.0);
    ans = min(ans, m*x + days*p);
  }
  
  printf("%.3f\n", ans);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

// K : dias que UM pintor usa para pintar tudo (K/M para pintar quando tem M pintores) 
// P : deve-se pagar (K/M)*P de penalidade 
// X : valor para contratar cada pintor

// custo = M*X + (K/M)*P
