#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MOD 1000000007LL
void mult(ll a[][2], ll b[][2]) {
	ll c[2][2];
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			ll r = 0;
			for(int k = 0; k < 2; ++k)
				r += a[i][k] * b[k][j];
			c[i][j] = r % MOD;
		}
	}
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 2; ++j)
			a[i][j] = c[i][j];
}
void matrix_pow(ll a[][2], ll m[][2], ll p) {
	if(p == 0) {
		a[0][0] = a[1][1] = 1;
		a[1][0] = a[0][1] = 0;
	}
	else {
		matrix_pow(a, m, p >> 1);
		mult(a, a);
		if(p & 1) mult(a, m);
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n;
	cin >> n;
	if(n < 2) cout << n << '\n';
	else {
		ll m[][2] = {{1, 1}, {1, 0}};
		ll a[2][2];
		matrix_pow(a, m, n - 1);
		cout << a[0][0] << '\n';	
	}
	return 0;
}
