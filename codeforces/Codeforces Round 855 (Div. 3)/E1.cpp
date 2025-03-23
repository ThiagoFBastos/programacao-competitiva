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
	int n, k;
	string s, t;
	cin >> n >> k >> s >> t;
	auto a = s;
	auto b = t;
	sort(all(a)); sort(all(b));
	if(a != b) {
		cout << "NO\n";
		return;
	}
	if(n >= 6) cout << "YES\n";
	else if(n == 4) {
		if(s == t) {
			cout << "YES\n";
			return;
		}
		swap(s.front(), s.back());
		if(s == t) {
			cout << "YES\n";
			return;
		}
		cout << "NO\n";
	} else if(n == 5) {
		if(s[2] == t[2]) cout << "YES\n";
		else cout << "NO\n";
	} else if(s == t) cout << "YES\n";
	else cout << "NO\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
