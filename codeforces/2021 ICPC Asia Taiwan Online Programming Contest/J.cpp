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

bool isNumber(string str)
{
  int n = str.size();
  for(int i=0; i<n; i++)
  {
    if(!isdigit(str[i]))
      return false;
  }
  
  return true;
}

void solve() {
  string x,y;
  cin >> x >> y;
  
  if(!isNumber(x) || !isNumber(y))
    cout << "NaN\n";
    
  else
  {
    int numX = stoi(x);
    int numY = stoi(y);
    
    cout << numX - numY << "\n";
  } 
  
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

