#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

void solve() {
	
	int n, zeroes = 0;

	cin >> n;

	vector<int> a(n);

	for(int i = 1; i <= n; ++i) {
		int v;
		cin >> v;
		zeroes += __builtin_ctz(v);
		a[i - 1] = __builtin_ctz(i);
	}

	sort(rall(a));

	int ans = 0;

	for(int v : a) {
		if(zeroes >= n) break;
		++ans;
		zeroes += v;
	}

	if(zeroes < n) {
		cout << "-1\n";
		return;
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
