#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e3, MOD = 1e9 + 7; 
int expmod(int n, int p) {
	if(p == 0) return 1;
	int r = expmod(n, p >> 1);
	r = 1LL * r * r % MOD;
	return p & 1 ? 1LL * r * n % MOD : r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int B, G, **C;
	C = new int*[MAXN + 1];
	for(int i = 0; i <= MAXN; ++i)
		C[i] = new int[MAXN + 1];
	C[0][0] = 1;
	for(int i = 1; i <= MAXN; ++i) {
		C[i][0] = C[i][i] = 1;
		for(int k = 1; k < i; ++k)
			C[i][k] = (C[i - 1][k] + C[i - 1][k - 1]) % MOD;
	}
	while(true) {
		cin >> B >> G;
		if(!(B || G)) break;
		int resp = 0;
		for(int k = 1; k < G; ++k) {
			if(k & 1) resp = (resp + 1LL * C[G][k] * expmod(G - k, B)) % MOD;
			else resp = (resp - 1LL * C[G][k] * expmod(G - k, B)) % MOD;
		}
		cout << ((expmod(G, B) - resp) % MOD + MOD) % MOD << '\n';
	}
	return 0;
}