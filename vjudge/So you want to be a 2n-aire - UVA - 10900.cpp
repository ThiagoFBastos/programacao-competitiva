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
while(1) {
	int n;
	double t, E = 1, ans = 0;

	cin >> n >> t;

	if(n == 0) break;

	cout.precision(3);
	cout.setf(ios_base :: fixed);

	if(fabs(1 - t) < EPS) {
		cout << (1 << n) + 0.0 << '\n';
		continue;
	}
	
	for(int i = 0; i <= n; ++i) {
		ans = max(ans, E);
		double r = min(1.0, max(1 / (2 * E), t));
		E = (r - t + 2 * E * (0.5 - r * r / 2)) / (1 - t);
	}

	cout << ans << '\n';
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

