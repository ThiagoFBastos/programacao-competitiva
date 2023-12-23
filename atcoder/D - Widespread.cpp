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
	int n, a, b;

	cin >> n >> a >> b;

	vector<i64> h(n);
	int l = 1, r = INF;

	for(i64& v : h) cin >> v;

	sort(all(h));

	while(l < r) {
		int m = (l + r) / 2;
		i64 A = m;
		for(i64 v : h) {
			v -= 1ll * m * b;
			if(v <= 0) continue;
			A -= (v + a - b - 1) / (a - b);
		}
		if(A >= 0) r = m;
		else l = m + 1;
	}

	cout << r << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

