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

i64 exp(i64 a, i64 p, i64 m) {
	i64 ans = 1;
	a %= m;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * a % m;
		a = a * a % m;
	}
	return ans;
}

i64 f(i64 a, i64 n, i64 m) {
	if(n == 0) return 1;
	i64 mid = (n - 1) / 2;
	i64 p = f(a, mid, m), q = 0;
	q = exp(a, mid + 1, m) * p % m;
	if(~n & 1) q = (q + exp(a, n, m)) % m;
	return (p + q) % m;
}

void solve() {
	i64 x, a, m;
	cin >> a >> x >> m;
	cout << f(a, x - 1, m) % m << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}

