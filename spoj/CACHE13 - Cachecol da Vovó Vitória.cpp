#include <bits/stdc++.h>
 
#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2")
 
#define f first
#define s second
 
using namespace std;
 
typedef long long ll;
 
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
 
#define MOD 1000000007
 
ll Y[2][2];
 
inline void mult(ll a[][2], ll b[][2]) {
 
	ll c[2][2];
 
	c[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
	c[0][1] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
	c[1][0] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
	c[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
 
	a[0][0] = c[0][0] % MOD;
	a[0][1] = c[0][1] % MOD;
	a[1][0] = c[1][0] % MOD;
	a[1][1] = c[1][1] % MOD;
}
 
void matrix_power(ll X[][2], ll p) {
 
	if(p == 0) {
 
		X[0][0] = 1;
		X[0][1] = 0;
		X[1][0] = 0;
		X[1][1] = 1;
	}
 
	else {
 
		matrix_power(X, p >> 1);
 
		mult(X, X);
 
		if(p & 1) mult(X, Y);
	}
}
 
int main() {
  
	ll X[2][2];
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	Y[0][0] = Y[0][1] = Y[1][0] = 2;
	Y[1][1] = 3;
 
	ll N;
 
	cin >> N;
 
	matrix_power(X, N - 1);
 
	ll F1 = 6 * (X[0][0] + X[0][1]) % MOD;
	ll F2 = 6 * (X[1][0] + X[1][1]) % MOD;
 
	cout << (F1 + F2) % MOD << '\n';	
 
    return 0;
} 