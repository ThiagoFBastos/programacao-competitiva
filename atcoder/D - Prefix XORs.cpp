#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

int XOR[1<<21];

void solve() {
	int n, m;

	cin >> n >> m;

	vector<int> a(n);

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		XOR[n - i - 1] = a[i];
	}

	int l = 32 - __builtin_clz(m + n);

	for(int i = 0; i < l; ++i) {
		for(int j = 0; j < (1<<l); ++j) {
			if(j & (1 << i))
				XOR[j] ^= XOR[j ^ (1 << i)];
		}
	}

	for(int i = 0; i < m; ++i) cout << XOR[~i & ((1<<l)-1)] << ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
