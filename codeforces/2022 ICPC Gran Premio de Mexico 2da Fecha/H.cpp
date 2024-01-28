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
	int n, x;

	cin >> n >> x;
	
	vector<int> a(n);
	i64 ans = 0;

	for(int& v : a) cin >> v;

	sort(all(a));

	int l = 0;

	for(int i = 0; i < n; ++i) {
		bool ok = false;
		for(int j = 0; j < i; ++j) ok = ok || a[i] % a[j] == 0;
		if(ok) continue;
		a[l++] = a[i];
	}

	n = l;
	a.resize(l);

	for(int i = 1; i < (1 << n); ++i) {
		i64 mul = 1;
		for(int j = 0; j < n && mul <= x; ++j) if((i >> j) & 1) mul *= a[j];
		ans += x / mul * (__builtin_popcount(i) & 1 ? 1 : -1);
	}		

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

