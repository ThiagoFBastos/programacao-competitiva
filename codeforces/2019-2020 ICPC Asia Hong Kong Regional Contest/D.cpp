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
  int k, X;
  
  cin >> k >> X;
  
  string Y;
  
  while(X > 0) {
    int d = X % k;
    if(d == 0) d = k;
    Y += 10 - k + d - 1 + '0';
    X = (X - 1) / k;
  }
  
  reverse(Y.begin(), Y.end());
  
  cout << Y << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}

