#include "bits/stdc++.h"

using namespace std;

 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int mod = 1e9 + 7;

int cnt[61][2][2];

int count(i64 l, i64 r) {
	
	int msb = 63 - __builtin_clzll(r);

	for(int i = 0; i <= msb; ++i)
	for(int j = 0; j < 2; ++j)
	for(int k = 0; k < 2; ++k)
		cnt[i][j][k] = 0;

	cnt[msb][0][0] = 1;

	for(int i = msb - 1; i >= 0; --i) {
		int X = !!(l & (1ll << i));
		int Y = !!(r & (1ll << i));
		for(int k = 0; k < 2; ++k) {
			for(int j = 0; j < 2; ++j) {
				for(int a = 0; a <= 1; ++a) {
					for(int b = 0; b <= a; ++b) {						
						if(!k && a > Y || !j && b > X) continue;
						int& Z = cnt[i][k || a < Y][j || b < X];
						Z += cnt[i + 1][k][j];
						if(Z >= mod) Z -= mod;
					}
				}
			}
		}
	}

	int ans = 0;

	for(int i = 0; i < 2; ++i)
	for(int j = 0; j < 2; ++j)
		ans = (ans + cnt[0][i][j]) % mod;

	return ans;
}

void solve() {
	i64 l, r;
	int ans = 0;
	cin >> l >> r;
	for(int k = 0; (1ll << k) <= r; ++k) {
		i64 L = max(l, 1ll << k);
		i64 R = min(r, (2ll << k) - 1);
		if(L > R) continue;	
		ans = (ans + count(R, R)) % mod;
		if(L - 1 > (1ll << k)) ans = (ans - count(L - 1, R)) % mod;
	}
	cout << (ans + mod) % mod << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
