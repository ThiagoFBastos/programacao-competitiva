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
	vector<int> a(n), b(n);
	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;
	int lo = 0, hi = 1e9 + 1;
	sort(all(a));
	sort(all(b));
	while(lo < hi) {
		int m = (lo + hi) / 2;
		bool flag = false;
		for(int i = 0; i < n; ++i) {
			int hi = upper_bound(all(b), a[i] + m - 1) - b.begin();
			int lo = lower_bound(all(b), a[i] - m + 1) - b.begin();
			flag = flag || hi == lo;
		}
		if(!flag) hi = m;
		else lo = m + 1;
	}
	cout << max(0, hi - 1) << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
