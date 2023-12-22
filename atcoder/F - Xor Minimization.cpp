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

const int N = 1.5e5 + 10;

int n, a[N];

int rec(int k, int l, int r) {
	if(k < 0) {
		int ans = 0;
		for(; l <= r; ++l) ans = max(ans, a[l]);
		return ans;
	}

	int cur = l, cnt[2] = {0};	

	for(int i = l; i <= r; ++i) ++cnt[(a[i] >> k) & 1];
	
	if(max(cnt[0], cnt[1]) == r - l + 1) {
		for(int i = l; i <= r; ++i) a[i] &= ~(1 << k);
		return rec(k - 1, l, r);
	}

	for(int i = l; i <= r; ++i) {
		if(a[i] & (1 << k)) {
			swap(a[i], a[cur]);
			++cur;
		} else
			a[i] ^= 1 << k;
	}

	return min(rec(k - 1, l, cur - 1), rec(k - 1, cur, r));
}

void solve() {
	cin >> n;	
	for(int i = 0; i < n; ++i) cin >> a[i];
	cout << rec(29, 0, n - 1) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
