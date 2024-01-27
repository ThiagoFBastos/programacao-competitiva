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
	cin >> n >> k;
	cin.ignore();
	map<string, ii> mp;
	vector<pair<ii, string>> str;
	for(int i = 0; i < 3 * n; ++i) {
		string s;
		getline(cin, s);
		ii& x = mp[s];
		++x.fi, x.sc = i;
	}
	for(auto& [s, v] : mp) str.pb({v, s});
	sort(rall(str));
	for(int i = 0; i < min((int)str.size(), k); ++i) cout << str[i].sc << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
