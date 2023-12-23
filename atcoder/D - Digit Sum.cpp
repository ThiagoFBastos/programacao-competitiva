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

i64 f(i64 n, i64 b) {
	i64 s = 0;
	for(; n > 0; n /= b) s += n % b;
	return s;
}

void solve() {
	i64 n, s;

	cin >> n >> s;

	for(int b = 2; 1ll * b * b <= n; ++b) {
		if(f(n, b) == s) {
			cout << b << '\n';
			return;
		}
	}

	i64 B = INFLL;

	if(f(n, n + 1) == s) B = n + 1;

	for(int b = 1; 1ll * b * b <= n; ++b) {
		i64 mod = s - b;
		
		if(n < mod || (n - mod) % b) continue;

		i64 k = (n - mod) / b;

		if(k > 1 && f(n, k) == s) B = min(B, k);		
	}

	if(B == INFLL) {
		cout << "-1\n";
		return;
	}

	cout << B << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
