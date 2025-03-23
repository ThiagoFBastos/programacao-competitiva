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
	int ev1, ev2, at, d;

	cin >> ev1 >> ev2 >> at >> d;
if(!ev1) break;
	array<double, 50> ev[2];
	
	ev[0].fill(0);
	ev[0][ev1 + 10] = 1.0;

	for(int i = 0; i < 1000; ++i) {
		ev[1].fill(0);
		for(int j = 0; j <= 30; ++j) {
			if(j - 10 <= 0 || ev2 - max(0, j - 10 - ev1) <= 0) {
				ev[1][j] += ev[0][j];
				continue;
			}
			ev[1][j + d] += ev[0][j] * at / 6.0;
			ev[1][j - d] += ev[0][j] * (6 - at) / 6.0;
		}
		swap(ev[0], ev[1]);
	}

	double ans = 0;
	for(int j = 0; j <= 30; ++j) if(ev2 - max(0, j - 10 - ev1) <= 0) ans += ev[0][j];

	cout << fixed << setprecision(1) << 100 * ans << '\n';
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

