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

const int N = 1 << 20, MOD = 998244353;

ii f[N];

ii merge(ii f, ii g) {
	ii h;
	h.fi = (i64)f.fi * g.fi % MOD;
	h.sc = ((i64)f.fi * g.sc + f.sc) % MOD;
	return h;
}

void upd(int k, int a, int b, int l, int r, int n = 1) {
	if(l == r) f[n] = {a, b};
	else {
		int m = (l + r) / 2;
		if(k <= m) upd(k, a, b, l, m, 2 * n);
		else upd(k, a, b, m + 1, r, 2 * n + 1);
		f[n] = merge(f[2 * n + 1], f[2 * n]);	
	}
}

ii query(int l, int r, int lo, int hi, int n = 1) {
	if(l > r) return {1, 0};
	else if(r - l == hi - lo) return f[n];
	int m = (lo + hi) / 2;
	ii f = query(l, min(r, m), lo, m, 2 * n);
	ii g = query(max(m + 1, l), r, m + 1, hi, 2 * n + 1);
	return merge(g, f);
}

void solve() {
	int q;

	cin >> q;

	int l = 0, r = 0;

	for(int i = 0; i < q; ++i) {
		int t;
		cin >> t;
		if(t == 0) {
			int a, b;
			cin >> a >> b;
			upd(r, a, b, 0, q - 1);
			++r;
		} else if(t == 1) ++l;
		else {
			int x;
			cin >> x;
			auto [a, b] = query(l, r - 1, 0, q - 1);
			cout << (1ll * a * x + b) % MOD << '\n';
		}
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