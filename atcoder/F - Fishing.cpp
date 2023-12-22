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

bool get(int x0, int v0, int x1, int v1, int A, double& t1, double& t2) {

	if(v0 == v1) {
		if(x0 > x1 || abs(x1 - x0) > A) return false;
		t1 = 0, t2 = INF;
		return true;
	}

	double x = (x1 - x0) / double(v0 - v1);
	double l, r;

	if(x >= 0) {
		if(x0 <= x1) l = 0, r = x;
		else l = x, r = INF;
	} else {
		if(x0 > x1) return false;
		l = 0, r = INF;
	}

	t1 = (A - x0 + x1) / double(v0 - v1);
	t2 = (A - x1 + x0) / double(v1 - v0);

	if(t1 > t2) swap(t1, t2);

	t1 = max(l, t1);
	t2 = min(r, t2);

	return t2 - t1 > -EPS;
}

void solve() {
	int n, a;

	cin >> n >> a;

	vector<int> w(n), x(n), v(n);

	for(int i = 0; i < n; ++i) cin >> w[i] >> x[i] >> v[i];

	int ans = 0;

	for(int i = 0; i < n; ++i) {
		vector<tuple<double, int, int>> sweep;
		int tot = 0, best = 0;
		for(int j = 0; j < n; ++j) {
			if(i == j) continue;
			double l, r;
			if(!get(x[i], v[i], x[j], v[j], a, l, r)) continue;
			sweep.pb({l, 0, w[j]});
			sweep.pb({r + EPS, 1, w[j]});
		}
		sort(all(sweep));
		for(auto [x, t, w] : sweep) {
			if(t == 0) tot += w;
			else tot -= w;
			best = max(best, tot);
		}
		ans = max(ans, best + w[i]);
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
