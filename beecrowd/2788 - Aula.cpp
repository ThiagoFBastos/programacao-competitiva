#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvii = vector<vii>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

int digitos(ull);

int digitos(ull n) {
	int ans {};
	ull p = 1;
	while(p <= n) {
		++ans;
		p *= 10;
	}
	return max(1, ans);
}

const int maxn = 2e5 + 1;
ull n, p[20], pm[20], pmn[20], res = ULLONG_MAX;
int m, d, digits[20][maxn], dn;
ii dp[20][maxn];

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	dn = digitos(n);
	d = dn + digitos(m);

	p[0] = pm[0] = 1;
	pmn[0] = n % m;

	for(int i = 1; i <= 19; ++i) {
		p[i] = 10 * p[i - 1];
		pm[i] = 10 * pm[i - 1] % m;
		pmn[i] = 10 * pmn[i - 1] % m;
	}

	for(int i = 0; i <= d; ++i)
		for(int k = 0; k < m; ++k)
			dp[i][k] = make_pair(m + 1, 20);

	for(int i = 0; i < m; ++i) {
		int q_d = digitos(i);
		for(int k = 1; k <= d; ++k) {
			int y = pm[k] * i % m;
			dp[k][y] = min(dp[k][y], make_pair(i, q_d));
		}
	}

	for(int k = 0; k < m; ++k) {
		int dk = digitos(k);
		ll x = p[dk] * n;
		if(x > res) break;
		for(int i = dk; dn + i <= d && x < res; ++i) {

			int z = pmn[i] + k;

			if(z >= m) 
				z -= m;
			
			if(dp[dn + i][m - z].second + dn + i <= d)
				res = min(res, p[dn + i] * dp[dn + i][m - z].first + x + k);

			x *= 10;
		}
	}

	if(dn + dp[dn][m - n % m].second <= d)
		res = min(res, n + p[dn] * dp[dn][m - n % m].first);

	cout << res << '\n';
	return 0;
}