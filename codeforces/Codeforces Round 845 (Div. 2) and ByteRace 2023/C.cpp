#include "bits/stdc++.h"

using namespace std;

#define INF    1000000000
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

const int N = 2e5 + 10;

int fac[N];

vector<int> D(int n) {
	vector<int> d {1};
	while(n != 1) {
		int m = d.size(), pt = 1, p = fac[n];
		while(n % p == 0) {
			n /= p;
			pt *= p;
			for(int i = 0; i < m; ++i) d.pb(d[i] * pt);
		}
	}
	return d;
}

void solve() {
	
	int n, m;

	cin >> n >> m;

	vector<int> a(n), last(m + 1, INF);
	set<ii> st;	

	for(int& v : a) cin >> v;
		
	sort(all(a));
	a.resize(unique(all(a)) - a.begin());

	int ans = INF;

	for(int i = 1; i <= m; ++i) st.emplace(INF, i);

	for(int i = (int)a.size() - 1; i >= 0; --i) {
		for(int j : D(a[i])) {
			if(j > m) continue;
			st.erase(ii(last[j], j));
			last[j] = a[i];
			st.emplace(a[i], j);
		}
		ans = min(ans, st.rbegin()->fi - a[i]);
	}

	if(ans > N) cout << "-1\n";
	else cout << ans << '\n';
}

int main() {
	for(int i = 2; i < N; ++i) {
		if(fac[i]) continue;
		for(int j = i; j < N; j += i) fac[j] = i;
	}
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
