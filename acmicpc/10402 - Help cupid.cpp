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

int d(int t1, int t2) {
	return min(abs(t1-t2), 24 - abs(t1-t2));
}

void solve() {
	int n;

	cin >> n;

	vector<int> a(n);
	int best = INF;

	for(int& v : a) cin >> v;

	sort(all(a));
	
	for(int k = 0; k < 2; ++k) {
		for(int i = 0; i < n; ++i) {
			int t = 0;
			for(int j = 0; j < n; j += 2)
				t += d(a[(i+j)%n], a[(i+j+1)%n]);
			best = min(best, t);
		}
		reverse(all(a));
	}

	cout << best << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
