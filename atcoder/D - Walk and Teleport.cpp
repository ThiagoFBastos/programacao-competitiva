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
	int n, a, b;

	cin >> n >> a >> b;

	vector<int> x(n);

	for(int& v : x) cin >> v;

	vector<i64> d;

	for(int i = 1; i < n; ++i) d.pb(x[i] - x[i - 1]);

	sort(rall(d));

	d.insert(d.begin(), 0);

	for(int i = 1; i < (int)d.size(); ++i) d[i] += d[i - 1];

	i64 ans = INFLL, dist = x.back() - x.front();
	
	for(int i = 0; i < n; ++i)
		ans = min(ans, a * (dist - d[i]) + 1ll * b * i);
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
