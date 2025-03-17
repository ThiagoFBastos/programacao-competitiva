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


set<string> S;

void solve() {	
	int k;
	string s;
	cin >> k >> s;
	cout << (S.count(s) ? "YES\n" : "NO\n");	
}

int main() {
	string s;
	for(int k = 1; k <= 1e4; ++k) {
		if(k % 3 == 0) s += 'F';
		if(k % 5 == 0) s += 'B';
	}
	int n = s.size();
	for(int k = 0; k < n; ++k)
		for(int l = 1; l <= 10 && k + l <= n; ++l)
			S.insert(s.substr(k, l));
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
