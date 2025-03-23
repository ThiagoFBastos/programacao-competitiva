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

vector<ii> P(int x) {
	vector<ii> p;
	for(int k = 2; k * k <= x; ++k) {
		if(x % k) continue;
		int i = 0;
		while(x % k == 0) x /= k, ++i;
		p.pb({k, i});
	}
	if(x > 1) p.pb({x, 1});
	return p;
}

void solve() {
	int a, b, c, d;

	cin >> a >> b >> c >> d;

	map<int, int> p;
	vector<i64> D {1};

	for(auto [x, k] : P(a)) p[x] += k;
	for(auto [x, k] : P(b)) p[x] += k;

	for(auto [x, k] : p) {
		int n = D.size();
		i64 y = 1;
		for(int i = 0; i < k; ++i) {
			y *= x;
			for(int j = 0; j < n; ++j) {
				i64 z = D[j] * y;
				if(z > max(d, c)) continue;
				D.pb(z);
			}
		}
	}

	for(i64 g : D) {
		i64 h = (i64)a * b / g;
		if(d / h - b / h > 0 && c / g - a / g > 0) {
			i64 x = a + 1, y = b + 1;
			x = x + (g - x % g) % g;
			y = y + (h - y % h) % h;
			cout << x << ' ' << y << '\n';
			return;
		}
	}
	
	cout << "-1 -1\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
