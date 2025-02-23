#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("mmx", "sse", "sse2", "sse3", "sse4")

#include "bits/stdc++.h"

using namespace std;

using ll = long long;
using li = pair<ll, int>;
using ii = pair<int, int>;

const int N = 200001;
const ll MAXN = 4e10L;

int fac[N], mobius[N];
vector<ii> S;
vector<ll> ans;
vector<li> a;

ll count(ll maxn) {
	ll cnt = maxn;
	for(auto [x, mbs] : S) {
		ll y = 1ll * x * x;
		if(y > maxn) break;
		cnt -= maxn / y * mbs;
	}
	return cnt;
}

void solve(ll lo, ll hi, int l, int r) {
	if(l > r) return;
	else if(lo == hi) {
		for(; l <= r; ++l) ans[a[l].second] = hi;
	} else if(l == r) {
		while(lo < hi) {
			ll mid = (lo + hi) / 2;
			if(count(mid) >= a[l].first) hi = mid;
			else lo = mid + 1;
		}
		ans[a[l].second] = hi;
	} else {
		ll mid = (lo + hi) / 2;
		ll cnt = count(mid);
		int k = upper_bound(a.begin(), a.end(), make_pair(cnt, INT_MAX)) - a.begin();
		solve(lo, mid, l, k - 1);
		solve(mid + 1, hi, k, r);
	}
}

void solve() {
	int q;
	cin >> q;
	
	a.resize(q);
	ans.resize(q);
	
	for(int i = 0; i < q; ++i) {
		ll n;
		cin >> n;
		a[i] = {n, i};
	}
	
	sort(a.begin(), a.end());
	
	solve(1, MAXN, 0, q - 1);
	
	for(ll cnt : ans) cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	for(int k = 2; k < N; ++k) {
		if(fac[k]) continue;
		for(int j = k; j < N; j += k) fac[j] = k;
	}
	
	mobius[1] = -1;
	
	for(int k = 2; k < N; ++k) {
		int i = k / fac[k];
		if(fac[i] == fac[k]) mobius[k] = 0;
		else mobius[k] = -mobius[i];
		if(mobius[k]) S.emplace_back(k, mobius[k]);
	}

	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}