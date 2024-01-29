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

const int N = 1e6 + 100, MOD = 1e9 + 7;

i64 pot[N];
int fac[N], mobius[N];

vector<int> divisors(int n) {
  vector<int> d {1};
  while(n > 1) {
    int p = fac[n];
    int m = d.size();
    i64 q = 1;
    while(n % p == 0) {
      q *= p;
      n /= p;
      for(int i = 0; i < m; ++i) d.push_back(d[i] * q);
    }
  }
  return d;
}

void solve() {
  int k;
  cin >> k;
  i64 ans = 0;
  for(int a : divisors(k)) {
    ans += mobius[k / a] * pot[a];
    if(ans >= MOD) ans -= MOD;
    else if(ans < 0) ans += MOD;
  }
  cout << ans << '\n';
}

int main() {
  
  pot[0] = 1;
  for(int i = 1; i < N; ++i) {
    pot[i] = pot[i - 1] << 1;
    if(pot[i] >= MOD) pot[i] -= MOD;
  }
  
  memset(mobius, -1, sizeof mobius);
  mobius[1] = 0;
    
  for(int k = 2; k < N; ++k) {
    if(fac[k]) continue;
    for(int i = k; i < N; i += k) {
        fac[i] = k;
        mobius[i] *= -1;
    }
    i64 p = (i64)k * k;
    if(p >= N) continue;
    for(int i = p; i < N; i += p) mobius[i] = 0;
  }
  
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}


