#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

int n;
vector<i64> base;
i64 xor_all;

bool canMake(i64 x, i64 mask) {
	x &= mask;
	for(i64 y : base) {
		y &= mask;
		x = min(x, x ^ y);
	}
	return !x;
}

void solve() {

	cin >> n;

	base.resize(n);

	for(i64& v : base) {
		cin >> v;
		xor_all ^= v;
	}

	for(i64& v : base) v &= ~xor_all;

	for(int i = 59, j = 0; i >= 0; --i) {
		for(int k = j; k < n; ++k) {
			if(base[k] & (1ll << i)) {
				swap(base[k], base[j]);
				break;
			}
		}
		if((~base[j] & (1ll << i))) continue;
		for(int k = j + 1; k < n; ++k) {
			if(base[k] & (1ll << i))
				base[k] ^= base[j];
		}
		++j;
	}

	i64 a = 0;
	
	for(int i = 59; i >= 0; --i) {
		int bit = (xor_all >> i) & 1;
		if(!bit && canMake(a | (1ll << i), ~((1ll << i) - 1))) a |= 1ll << i;
	}
	
	cout << a + (xor_all ^ a) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
 
