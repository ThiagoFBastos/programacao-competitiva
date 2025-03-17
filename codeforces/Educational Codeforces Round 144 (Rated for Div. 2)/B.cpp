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
	string a, b;
	cin >> a >> b;
	int n = a.size(), m = b.size();
	if(a[0] == b[0]) {
		cout << "YES\n";
		cout << a[0] << "*\n";
	} else if(a.back() == b.back()) {
		cout << "YES\n";
		cout << "*" << a.back() << '\n';
	} else {
		for(int i = 0; i <= n - 2; ++i) {
			string s = a.substr(i, 2);
			for(int j = 0; j <= m - 2; ++j) {
				if(b.substr(j, 2) == s) {
					cout << "YES\n";
					cout << "*" << s << "*\n";
					return;
				}
			}
		}
		cout << "NO\n";
	}
}

int main() {
	
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
