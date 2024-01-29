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
  i64 max_sum;
  string memo;
  
  cin >> n >> memo;
  
  char type = memo.back();
  memo.pop_back();
  
  max_sum = stoi(memo);
  
  if(type == 'G') max_sum *= 1024;
  else if(type == 'T') max_sum *= 1024 * 1024;

  vector<int> a(n);
  for(int& v : a) cin >> v;
  
  vector<i64> pre(n + 1, 0);
  for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i - 1];
  
  int l = 1, r = n + 1;
  
  while(l < r) {
    int mid = (l + r) / 2; 
    i64 sum = 0;
    for(int i = 1; i + mid - 1 <= n; ++i) sum = max(sum, pre[i + mid - 1] - pre[i - 1]);
    if(sum > max_sum) r = mid;
    else l = mid + 1;
  }
  
  --r;
  
  for(int i = 1; i + r <= n; ++i) {
    if(pre[i + r] - pre[i - 1] > max_sum) {
      cout << r << ' ' << i << '\n';
      return;
    }
  }
  
  cout << r << ' ' << "-1\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


