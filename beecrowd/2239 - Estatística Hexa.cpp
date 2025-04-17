#pragma GCC optimize("O3")
#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;

int digit(char ch) {
	if(isdigit(ch)) return ch - '0';
	return ch - 'a' + 10;
}

i64 maxSum[1 << 16], minSum[1 << 16], parcial[1 << 16], fat[17], sum;

void solve() {
	string _n;
	int n = 0;

	cin >> _n;

	for(char ch : _n) {
		n <<= 4;
		n += digit(ch);
	}

	vector<i64> a(n);

	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		a[i] = 0;
		for(char ch : s) {
			a[i] <<= 4;
			a[i] += digit(ch);
		}
	}

	fat[0] = 1;
	for(int i = 1; i <= 16; ++i) fat[i] = (i64)i * fat[i - 1] % MOD;

	for(int i = 1; i < (1 << 16); ++i) {
		maxSum[i] = LLONG_MIN;
		minSum[i] = LLONG_MAX;
		parcial[i] = 0;

		for(i64 s : a) {
			int k = 0;
			while(s > 0) {
				int d = s & 15;
				if(~i & (1 << d)) {
					parcial[i] += (i64)d << k;
					k += 4;
				}
				s >>= 4;
			}
		}

		int m = __builtin_popcount(i);

		sum = (sum + parcial[i] % MOD * fat[m] % MOD * fat[16 - m]) % MOD; 

		for(int j = 0; j < 16; ++j) {
			if(i & (1 << j)) {
				maxSum[i] = max(maxSum[i], maxSum[i ^ (1 << j)] + parcial[i]);
				minSum[i] = min(minSum[i], minSum[i ^ (1 << j)] + parcial[i]);
			}
		}
	}
	
	cout << hex << minSum[(1<<16)-1] << ' ' << hex << maxSum[(1<<16)-1] << ' ' << hex << sum << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 