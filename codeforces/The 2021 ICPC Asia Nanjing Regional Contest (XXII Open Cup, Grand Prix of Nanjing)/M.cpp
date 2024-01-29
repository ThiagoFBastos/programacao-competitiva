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
	int n;

	cin >> n;

	vector<int> a(n);
	i64 s = 0, ans = LLONG_MIN;
	multiset<int> S;
  
	for(int& v : a) {
		cin >> v;
		s += abs(v);
    S.insert(v);
	}
  
  if(n == 1) {
    cout << a[0] << '\n';
    return;
  }

  for(int& v : a) {
      S.erase(S.find(v));
      i64 X = s - abs(v) - abs(*S.begin());
      ans = max(ans, X + v - *S.begin());
      S.insert(v);
  }
  
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}

