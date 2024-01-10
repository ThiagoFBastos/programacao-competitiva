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

void solve() {
	string s;
	int n, p;	
	i64 cnt {};
	cin >> n >> p >> s;
	if(p == 2) {
		for(int i = 1; i <= n; ++i) cnt += (s[i-1]+1)%2*i;
	} else if(p == 5) {
		for(int i = 1; i <= n; ++i) cnt += !((s[i-1]-'0')%5)*i;
	} else {
		int h = 0, pt = 1;
		map<int, int> frq {{0,1}};
		reverse(all(s));
		for(char c : s) {
			pt = 10 * pt % p;
			h = (h + (c-'0')*pt)%p;
			cnt += frq[h]++;
		}
	}
	cout << cnt << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
