#include "bits/stdc++.h"

using namespace std;
 
#define INF   10000000000ll
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
	int n, k;
	int lc, pc, lm, pm;
	int t, d;

	cin >> n >> k;
	cin >> lc >> pc >> lm >> pm;
	cin >> t >> d;
	
	vector<int> a(n);
	vector<i64> needm(n + 1, 0), needc(n + 1, 0);
	vector<i64> extrap(n + 1, 0), extram(n + 1, 0), extrac(n + 1, 0);
	i64 ans = INFLL;

	for(int& v : a) cin >> v;

	sort(all(a));

	for(int i = 1; i <= n; ++i) {
		extrap[i] = extrap[i - 1] + min(a[i - 1] - 1, d);
		extram[i] = extram[i - 1] + max(min(d, a[i - 1] - lm), 0);
		extrac[i] = extrac[i - 1] + max(min(d, a[i - 1] - lc), 0);
		needm[i] = needm[i - 1];
		needc[i] = needc[i - 1];
		if(lm - a[i - 1] <= d) needm[i] += max(0, lm - a[i - 1]);
		else needm[i] += INF;
		if(lc - a[i - 1] <= d) needc[i] += max(0, lc - a[i - 1]);
		else needc[i] += INF;
	}

	for(int i = 0; i <= n; ++i) {
		i64 lo = i * (k - 1ll) + 1, hi = n - i;
		if(lo <= hi) {
			i64 need = needc[n] - needc[hi] + needm[hi] - needm[lo - 1];
			i64 extra = extrap[lo - 1] + extram[hi] - extram[lo - 1] + extrac[n] - extrac[hi];
			if(need <= extra) {
				i64 cost = need * t + (i64)i * pc + (hi - lo + 1ll) * pm;
				ans = min(ans, cost);
			}
		} else {
			i64 need = needc[n] - needc[hi];
			i64 extra = extrap[hi] + extrac[n] - extrac[hi];
			if(need <= extra) {
				i64 cost = need * t + (i64)i * pc;
				ans = min(ans, cost);
			}
		}
	}

	if(ans == INFLL) {
		cout << "-1\n";
		return;
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
