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

int check_valid(int n)
{
 while (n > 10)
 {
    if (n%10 == 0)
      return 0;
    n/=10;
 }
  return 1;
}

void solve() {
  int n; cin >> n;
  int ans = n;
  ans++;
  string s = to_string(ans);
  for(int i = 0; i < s.size(); i++)
  {
    if (s[i] == '0')
      s[i] = '1';
  }
  cout << s << "\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

