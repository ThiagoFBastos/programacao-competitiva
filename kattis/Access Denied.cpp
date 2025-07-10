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

int certo(int tamanho) {
  return 14 + tamanho * 9;
}

void solve() {
     int len = 0;
     
   while(true) {
     string s;
     int t;
     ++len;
     cout << string(len, 'A') << '\n';
     cout.flush();
     getline(cin, s);
     if(s == "ACCESS GRANTED") return;
     sscanf(s.c_str(), "%*s %*s (%d ms)", &t);
     if(t != 5) break;
   }
  
   string alpha, ans(len, 'A');
   
   for(int i = 0; i < 10; ++i) alpha += '0' + i;
   for(int i = 0; i < 26; ++i) alpha += 'A' + i;
   for(int i = 0; i < 26; ++i) alpha += 'a' + i;
   
   for(int i = 0; i < len; ++i) {
     for(char ch : alpha) {
          ans[i] = ch;
          int t;
          string s;
          cout << ans << '\n';
          cout.flush();
          getline(cin, s);
          if(s == "ACCESS GRANTED") return;
          sscanf(s.c_str(), "%*s %*s (%d ms)", &t);
          if(t >= certo(i + 1)) break;
      }
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