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

const int N = 101;

bool f(char c) {
  return c == 'x' || isdigit(c) || c == '-' || c == '+';
}

bool pare(char c) {
  return c == '+' || c == '-';
}

map<int, int> polynomial(string& s) {
  map<int, int> C;
  
  int n = s.size();
  vector<bool> vis(n, false);
  
  for(int i = 0; i < n; ++i) {
    if(vis[i]) continue;
    if(s[i] == '^') {
      string p, q;
      bool read_num = false;
      vis[i] = true;
      for(int k = i - 1; k >= 0; --k) {
         p += s[k];
         vis[k] = true;
         if(s[k] == '-' || s[k] == '+') break;
      }
      reverse(p.begin(), p.end());
      for(int k = i + 1; k < n; ++k) {
        if(!isdigit(s[k]) && read_num) break;
        vis[k] = true;
        q += s[k];
        read_num = read_num || isdigit(s[k]);
      }
      p.pop_back();
      if(p.back() == '+' || p.back() == '-' || p.empty()) p += '1';
     	C[stoi(q)] += stoi(p);
    }
  }
  
  for(int i = 0; i < n; ++i) {
    if(vis[i] || s[i] != 'x') continue;
     string p;
      vis[i] = true;
      for(int k = i - 1; k >= 0; --k) {
         p += s[k];
         vis[k] = true;
         if(s[k] == '-' || s[k] == '+') break;
      }
      reverse(p.begin(), p.end());
      if(p.back() == '+' || p.back() == '-' || p.empty()) p += '1';
     	C[1] += stoi(p);
  }
  
  return C;
}

void solve() {
	 string s;
   cin >> s;
   auto C = polynomial(s);
   bool ini = false;

   for(auto [x, y] : C) {
       y *= x;
       if(y) {
        if(ini) cout << (y >= 0 ? "+"s : ""s);
        cout << y;
        if(x == 2) cout << "x";
        else if(x != 1) cout << "x^" << x - 1;
        ini = true;
       }
    }
    
    if(!ini) cout << "0";
	
	cout<<'\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

