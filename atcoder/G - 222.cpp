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

int phi(int x) {
	int y = x;
	for(int p = 2; p * p <= x; ++p) {
		if(x % p) continue;
		y -= y / p;
		while(x % p == 0) x /= p;
	}
	if(x != 1) y -= y / x;
	return y;
}

int exp(int n, int k, int m) {
	int x = 1;
	for(; k; k >>= 1) {
		if(k & 1) x = (i64)x * n % m;		
		n = (i64)n * n % m;
	}
	return x;
}

void solve() {
	int m;

	cin >> m;

	if(m % 5 == 0) {
		cout << "-1\n";
		return;
	} else if(m == 1) {
		cout << "1\n";
		return;
	}

	m *= 9;

	if(~m & 1) m /= 2;

	if(~m & 1) {
		cout << "-1\n";
		return;
	}

	int k = phi(m);
	int ans = k;

	for(int i = 1; i * i <= k; ++i) {
		if(k % i) continue;
		if(exp(10, k / i, m) == 1) ans = min(ans, k / i);	
		if(exp(10, i, m) == 1) ans = min(ans, i);		
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
