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

void solve() {
	int l, r, len = 0, p = 1;

	cin >> l >> r;

	for(int k = l; k <= r; k <<= 1) {
		++len;
		p <<= 1;
	}

	p >>= 1;

	if(len == 1) {
		cout << "1 " << r - l + 1 << '\n';
		return;
	}

	const int MOD = 998244353;
	int ans = r / p - l + 1;

	for(int i = 0; i < len - 1; ++i) {
		i64 P = p * 3 / 2;
		if(l * P <= r) ans = (ans + r / P - l + 1) % MOD;
	}

	cout << len << " " << ans << '\n';
}

int main() {
	
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
