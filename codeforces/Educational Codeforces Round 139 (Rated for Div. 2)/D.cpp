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

const int N = 1e7 + 10;

int fac[N];

vector<int> D(int n) {
	vector<int> d;
	while(n != 1) {
		int p = fac[n];
		while(n % p == 0) n /= p;
		d.pb(p);
	}
	return d;
}

void solve() {
	int x, y, ans = INF;

	cin >> x >> y;

	for(int p : D(y - x)) ans = min(ans, (p - x % p) % p);

	cout << (ans == INF ? -1 : ans) << '\n';
}

int main() {
	for(int i = 0; i < N; ++i) fac[i] = i;
	for(int p = 2; p * p < N; ++p) {
		if(fac[p] != p) continue;
		for(int k = p * p; k < N; k += p) fac[k] = min(fac[k], p);
	}
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
