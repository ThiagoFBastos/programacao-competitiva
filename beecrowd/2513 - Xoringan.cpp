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

const int maxn = 1001, mod = 1e9 + 7;

ull p[maxn];
int bits[64], p2[64], n;

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	p2[0] = 1;
	
	for(int k = 1; k < 64; ++k) {
		p2[k] = p2[k - 1] << 1;
		if(p2[k] >= mod) 
			p2[k] -= mod;
	}

	while(cin >> n) {

		int res = 0;

		p[0] = 0;

		for(int i = 1; i <= n; ++i) {
			cin >> p[i];
			p[i] ^= p[i - 1];
		}

		memset(bits, 0, sizeof bits);

		for(int k = 1; k <= n; ++k) {
			for(int i = 0; i < 64; ++i) {
				if(p[k] & 1LLU << i)
					res = (res + 1LLU * p2[i] * (k - bits[i])) % mod;
				else	
					res = (res + 1LLU * p2[i] * bits[i]) % mod;
			}
			for(int i = 0; i < 64; ++i)
				bits[i] += (p[k] & 1LLU << i) != 0;				
		}
		cout << res << '\n';
	}

	return 0;
}