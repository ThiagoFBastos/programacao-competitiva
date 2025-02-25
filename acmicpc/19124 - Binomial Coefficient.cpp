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

i64 modMul(i64 a, i64 b, i64 p) {
	return (__int128)a * b % p;
}

void gcd(__int128 a, __int128 b, __int128& x, __int128& y) {
	if(!b) {
		x = 1;
		y = 0;
		return;
	}
	__int128 _x, _y;
	gcd(b, a % b, _x, _y);
	y = _x - (a / b) * _y;
	x = _y;	
}

i64 modInv(i64 x, i64 p) {
	__int128 a, b;
	gcd(x, p, a, b);
	a = (a + p) % p;
	return a;
}

i64 fastExp(i64 n, i64 p, i64 mod) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = modMul(ans, n, mod);
		n = modMul(n, n, mod);
	}
	return ans;
}

i64 sumRange(i64 l, i64 r) {
	return (__int128)(r + l) * (r - l + 1) / 2 & 0xffffffff;
}

i64 modRange(i64 l, i64 r) {
	i64 ans = 1;
	for(int k = 1; k < (1 << 16); k += 2) {
		i64 L = (l + (1 << 16) - k - 1) >> 16, R = (r - k) >> 16;

		i64 n = max(0ll, R - L + 1);

		if(!n) continue;

		i64 value = (modMul(sumRange(L, R), 1ll << 16, 1ll << 32) + k) & 0xffffffff;	
		value = modMul(value, fastExp(k, n - 1, 1ll << 32), 1ll << 32);
		ans = modMul(ans, value, 1ll << 32);
	}

	return ans;
}

pair<i64, __int128> findMod(i64 l, i64 r) {
	if(l > r) return {1ll, 0ll};
	
	i64 a = modRange(l, r);
	auto [b, c] = findMod((l + 1) / 2, r / 2);
	i64 even = (r - l + 1) / 2 + (~l & ~r & 1);
	
	return {modMul(a, b, 1ll << 32), c + even};
}

void solve() {
	i64 n, k;

	cin >> n >> k;

	k = min(k, n - k);

/*
	n(n-1)(n-2)*...*(n-k+1) / (1*2*3*4*...*k)

	mod de n(n-1)(n-2)(n-3)*...*(n-k) sem potência de 2
		. divide os numeros por mod (2^16)
		. (2^16 * n1 + x)(2^16 * n2 + x)(2^16 * n3 + x) * ... * (2^16n(m) + x) mod (2^32)
			.  x^(m - 1)(2^16 soma (ni) + x)
			. fica (2^16 * x^(m - 1) * soma (ni) + x^m) (mod 2^32) -> o resto é divisivel por 2^32
			. encontra (soma (a <= x + 2^16 * k) <= b - (mod * cnt))
		. se os números são impares -> não tem potência de 2 junto do modulo
		. encontra os módulos pra parte impar (fãcil) e a parte par (/ 2, guarda a potência e faz de novo)
		. gasta 2^16 por nivel e tem no máximo log(10^18) niveis

	. encontra o modulo da parte de cima e a potência de 2 
	. encontra o modulo da parte de baixo e a potência de 2
	. encontra o inverso modular da parte de baixo e 2^32
	. encontra X * (Y^-1) * (2^(de X) - 2^(de Y))
	. resolve o problema
*/

	auto [a, b] = findMod(n - k + 1, n);
	auto [c, d] = findMod(1, k);

	b -= d;
	c  = modInv(c, 1ll << 32);
	
	cout << modMul(modMul(a, c, 1ll << 32), 1ll << (int)min((__int128)32, b), 1ll << 32) << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	//cin >> t;
    while(t--) solve();
    return 0;
}

