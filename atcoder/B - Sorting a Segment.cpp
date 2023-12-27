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

const int N = 2e5 + 10;
const i64 M = (1ll << 61) - 1, P = 1817117;

int cnt[4 * N];
i64 h[4 * N], pt[N], hs[N];

void upd(int k, int x, int lo, int hi, int p = 1) {
	if(lo == hi) {
		cnt[p] += x;
		h[p] += k * x;
		return;
	}
	int m = (lo + hi) / 2;
	if(k <= m) upd(k, x, lo, m, 2 * p);
	else upd(k, x, m + 1, hi, 2 * p + 1);
	cnt[p] = cnt[2*p] + cnt[2*p+1];
	h[p] = (h[2 * p] + (i128)pt[cnt[2 * p]] * h[2 * p + 1]) % M;  
}

void solve() {
	int n, k;

	cin >> n >> k;

	vector<int> a(n);
	set<i64> HS;

	for(int& v : a) cin >> v;

	pt[0] = 1;
	for(int i = 1; i <= n; ++i) pt[i] = (i128)P * pt[i - 1] % M;

	for(int i = 1; i <= n; ++i) hs[i] = (hs[i - 1] + (i128)pt[i] * a[i - 1]) % M;
	
	for(int i = 0; i < k - 1; ++i) upd(a[i], 1, 0, n - 1);

	for(int i = 0; i <= n - k; ++i) {
		upd(a[i + k - 1], 1, 0, n - 1);
		i64 q = ((hs[n] - (hs[i + k] - hs[i]) + (i128)h[1] * pt[i + 1]) % M + M) % M;
		HS.insert(q);
		upd(a[i], -1, 0, n - 1);
	}

	cout << HS.size() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
