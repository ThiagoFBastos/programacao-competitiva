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

const int INF = 1e9;

void solve() {
   int K;
   
   cin >> K;
   
   int sqr = sqrt(K);
   
   int resto = K - sqr * sqr;
   int N = 2 * sqr + 1 + resto;
   int plus = 0;
   
   if(N > 100000) {
     plus = 1;
     resto = K - sqr * (sqr + 1);
     N = 2 * sqr + 2 + resto;
   }
   
   cout << N << '\n';
   
   for(int i = 2; i <= resto; ++i) cout << i - 1 << ' ';
   
   if(resto) cout << resto << ' ';
   
   int v = resto + 1;
   
   for(int i = 0; i < sqr; ++i) {
     if(i) cout << v << ' ';
     else cout << resto + 1 << ' ';
     ++v;
   }
   
   for(int i = 0; i < sqr + plus; ++i) {
     if(i) cout << v << ' ';
     else cout << resto + 1 << ' ';
     ++v;
   }
   
   cout << '\n';
   
   for(int i = 0; i < resto; ++i) cout << 2 << ' ';
   
   cout << INF << ' ';
   
   for(int i = 0; i < 2 * sqr + plus; ++i) cout << "1 ";
   
   cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

