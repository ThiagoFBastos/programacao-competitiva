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
using i128 = __int128;

void solve() {
	int n, m;

	cin >> n >> m;

	vector<int> a(n);
	vector<i64> ps(n + 1, 0);

	for(int& v : a) cin >> v;

	vector<ii> b(n);

	for(int i = 0; i < n; ++i) b[i] = {a[i], i};
	sort(all(b));
	b.pb({INF, 0});
	
	for(int i = 1; i <= n; ++i) ps[i] = ps[i - 1] + b[i - 1].fi;

	for(int i = n; i >= 0; --i) {
		if(m >= ps[i]) {
			if(i == 0 || i == n) cout << n - i + 1 << '\n';
			else if(ii(a[i], i) <= b[i - 1]) cout << n - i << '\n';
			else if(ps[i] + a[i] - b[i - 1].fi <= m) cout << n - i << '\n';
			else cout << n - i + 1 << '\n';
			break;
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
