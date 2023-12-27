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
	vector<int> a(n);
	for(int& v : a) cin >> v;
	auto p = a;
	sort(all(p));
	for(int& v : a) v = lower_bound(all(p), v) - p.begin();
	int swaps = 0;
	for(int i = 0; i < n; ++i) if(a[i] % 2 != i % 2) ++swaps;
	cout << swaps / 2 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
