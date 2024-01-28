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

i64 rev(int k) {
	i64 x = 0;
	while(k > 0) {
		x <<= 1;
		x += k & 1;
		k >>= 1;
	}
	return x;
}

i64 f(int k) {
	if(!k) return 0;
	int len = 32 - __builtin_clz(k);
	return ((i64)k << len) + rev(k);
}

i64 g(int k) {
	if(!k) return 0;
	int len = 32 - __builtin_clz(k);
	return ((i64)k << (len - 1)) + rev(k / 2);
}

void solve() {

	vector<int> A;

	for(int i = 1; i < (1 << 16); ++i) {
		A.pb(f(i));
		A.pb(g(i));
	}

	int q;

	cin >> q;

	sort(all(A));
	A.resize(unique(all(A)) - A.begin());

	for(int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		int lo = lower_bound(all(A), a) - A.begin();
		int hi = upper_bound(all(A), b) - A.begin();
		cout << hi - lo << '\n';
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

