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
	int n;
	cin >> n;
	vector<int> b(n - 1);
	for(int& v : b) cin >> v;
	vector<int> a(n);
	a[0] = b[0];
	a[n - 1] = b.back();
	for(int i = 0; i < n - 2; ++i) a[i + 1] = min(b[i], b[i + 1]);
	for(int v : a) cout << v << ' ';
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
