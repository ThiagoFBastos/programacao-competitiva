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
	set<ii> X, Y, Z;
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		X.emplace(y, z);
		Y.emplace(x, z);
		Z.emplace(x, y);
	}
	if(X.size() >= max(Y.size(), Z.size())) cout << "X\n";
	else if(Y.size() >= Z.size()) cout << "Y\n";
	else cout << "Z\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
 
