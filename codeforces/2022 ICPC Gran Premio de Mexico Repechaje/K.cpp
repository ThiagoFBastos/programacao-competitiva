#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

char chr(char c) {
  string s = "cfilosvz";
  for(int i = 0; i < (int)s.size(); ++i) {
    if(c <= s[i])
      return '2' + i;
  }
  return '\0';
}

void to(string& s) {
  for(char& c : s)
    c = chr(c);
}

void solve() {
  int n, m;
  cin >> n >> m;
  map<string, int> frq;
  while(n--) {
    string s;
    cin >> s;
    to(s);
    ++frq[s];
  }
  while(m--) {
    string s;
    cin >> s;
    cout << frq[s] << '\n';
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
