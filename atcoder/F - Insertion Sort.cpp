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

const int N = 2e5 + 10;

int n, p[N], a[N], b[N], c[N];
i64 psa[N], psb[N], psc[N], bit[N];

void upd(int k, i64 x) {
	for(; k <= n; k += k & -k) bit[k] = min(bit[k], x);
}

i64 query(int k) {
	i64 ans = INFLL;
	for(; k > 0; k -= k & -k) ans = min(ans, bit[k]);
	return ans;
}

void solve() {
	
	cin >> n;

	fill(bit, bit + n + 1, INFLL);

	for(int i = 0; i < n; ++i) cin >> p[i];

	for(int i = 0; i < n; ++i) {
		cin >> a[i] >> b[i] >> c[i];
		b[i] = min(a[i], b[i]);
		c[i] = min(a[i], c[i]);
	}
	
	for(int i = 1; i <= n; ++i) {
		psa[i] = psa[i - 1] + a[i - 1];
		psb[i] = psb[i - 1] + b[i - 1];
		psc[i] = psc[i - 1] + c[i - 1];
	}

	for(int i = 0; i < n; ++i) {
		int k = p[i];
		i64 cost = psb[k] - psa[k];
		upd(k, cost);
	}

	i64 ans = min(psb[n - 1], psc[n] - psc[1]);

	for(int i = 0; i < n; ++i) {
		i64 cost = min(query(p[i] - 1), 0ll) + psa[p[i] - 1];
		ans = min(ans, cost + psa[n] - psa[p[i]]);
		ans = min(ans, cost + psc[n] - psc[p[i]]);	
		upd(p[i], psb[p[i]-1] - psa[p[i]]);
		upd(p[i], cost - psa[p[i]]);
	}

	cout << ans << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
