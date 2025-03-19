#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

const int maxn = 1e5;
vvi M, Mt;
vector<ll> R, C;
int n, m;

ll solve() {

	ll ans = 0, a = 0, b = 0, c = 0, d = 0;

	for(int i = 0; i < n; ++i) {
		if(a < R[i]) {
			d = c;
			c = b;
			b = a;
			a = R[i];
		} else if(b < R[i]) {
			d = c;
			c = b;
			b = R[i];
		} else if(c < R[i]) {
			d = c;
			c = R[i];
		} else if(d < R[i])
			d = R[i];
	}

	ans = a + b + c + d;

	a = b = c = d = 0;

	for(int i = 0; i < m; ++i) {
		if(a < C[i]) {
			d = c;
			c = b;
			b = a;
			a = C[i];
		} else if(b < C[i]) {
			d = c;
			c = b;
			b = C[i];
		} else if(c < C[i]) {
			d = c;
			c = C[i];
		} else if(d < C[i])
			d = C[i];
	}

	ans = max(ans, a + b + c + d);

	if(n < m) {
		for(int i = 0; i < n; ++i) {
			for(int k = i + 1; k < n; ++k) {
				a = b = 0;
				for(int j = 0; j < m; ++j) {
					ll x = C[j] - M[i][j] - M[k][j];
					if(a < x) {
						b = a;
						a = x;
					} else if(b < x)
						b = x;
				}
				
				ans = max(ans, R[i] + R[k] + a + b);
			}
		}
	} else {
		for(int i = 0; i < m; ++i) {
			for(int k = i + 1; k < m; ++k) {
				a = b = 0;
				for(int j = 0; j < n; ++j) {
					ll x = R[j] - Mt[i][j] - Mt[k][j];
					if(a < x) {
						b = a;
						a = x;
					} else if(b < x)
						b = x;
				}
				ans = max(ans, C[i] + C[k] + a + b);	
			}
		}
	}
	
	for(int i = 0; i < m; ++i) {
		a = b = c = 0;
		for(int k = 0; k < n; ++k) {
			ll x = R[k] - Mt[i][k];
			if(a < x) {
				c = b;
				b = a;
				a = x;
			} else if(b < x) {
				c = b;
				b = x;
			} else if(c < x)
				c = x;
		}
		ans = max(ans, C[i] + a + b + c);
	}

	for(int i = 0; i < n; ++i) {
		a = b = c = 0;
		for(int k = 0; k < m; ++k) {
			ll x = C[k] - M[i][k];
			if(a < x) {
				c = b;
				b = a;
				a = x;
			} else if(b < x) {
				c = b;
				b = x;
			} else if(c < x)
				c = x;
		}
		ans = max(ans, R[i] + a + b + c);
	}

	return ans;
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	M.resize(n);
	Mt.resize(m);
	C.assign(m, 0);
	R.resize(n);

	for(int i = 0; i < m; ++i)	
		Mt[i].resize(n);

	for(int i = 0; i < n; ++i) {

		M[i].resize(m);
		R[i] = 0;

		for(int k = 0; k < m; ++k) {
			cin >> M[i][k];
			Mt[k][i] = M[i][k];
			R[i] += M[i][k];
			C[k] += M[i][k];
		}
	}

	cout << solve() << '\n';

	return 0;
}