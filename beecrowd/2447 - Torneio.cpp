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

const int mod = 1e9 + 7, maxn = 1 + (1 << 16);

int n, k, c[maxn], fat[maxn];

int expmod(int n, int p) {
	ll a = 1, b = n;
	while(p > 0) {
		if(p & 1)
			a = a * b % mod;
		b = b * b % mod;
		p >>= 1;
	}
	return a;
}

int P(int n, int k) {
	return 1LL * fat[n] * expmod(fat[n - k], mod - 2) % mod;
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k;

	fat[0] = 1;
	
	for(int i = 0; i < (1 << n); ++i) {
		cin >> c[i];
		fat[i + 1] = fat[i] * (1LL + i) % mod;
	}

	if(k == n + 1)
		cout << (*max_element(c, c + (1 << n)) > c[0] ? 0 : fat[1 << n]) << '\n';
	else {
		
		int p = 1 << k, l = 0, g = 0;

		n = 1 << n;

		for(int i = 1; i < n; ++i) {
			if(c[i] < c[0]) ++l;
			else ++g;
		}
		
		if(l < p / 2 - 1 || g == 0) cout << 0 << '\n';
		else {
			ll a, b;
			
			a = l < p - 1 ? P(l + g - p / 2 + 1, p / 2) : P(l + g - p / 2 + 1, p / 2) - P(l - p / 2 + 1, p / 2);
			b = p / 2LL * P(l, p / 2 - 1) % mod;
			
			if(a < 0) a += mod;

			cout << 2LL * a * b % mod * fat[n - p] % mod * (n / p) % mod << '\n';
		}
	}

	return 0;
}