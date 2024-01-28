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
	int n;

	cin >> n;

	vector<i64> x(n), y(n), r(n);

	for(i64& v : x) cin >> v;
	for(i64& v : r) cin >> v;

	sort(all(r));

	y[0] = 0;
	for(int i = 1; i < n; ++i) y[i] = x[i] - x[i - 1] - y[i - 1];
	
	if(n <= 2) {
		for(i64 x : r) cout << x << ' ';
		cout << '\n';
		return;
	}

	auto test = [&](vector<i64>& R) {
		for(int i = 1; i < n; ++i) if(R[i] + R[i - 1] != x[i] - x[i - 1]) return false;
		auto tmp = R;
		sort(all(tmp));
		return tmp == r;
	};

	for(int t : {1, 2}) {
		i64 max_y = -INFLL;
		for(int i = t; i < n; i += 2) max_y = max(max_y, y[i]);
		for(int i : {n - 2, n - 1}) {
			i64 r1 = max_y - r[i];
			if(t == 2) r1 *= -1;
			vector<i64> R(n);
			R[0] = r1;
			for(int i = 1; i < n; ++i) R[i] = x[i] - x[i - 1] - R[i - 1];
			if(test(R)) {
				for(i64& v : R) cout << v << ' ';
				cout << '\n';
				return;
			}
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}


