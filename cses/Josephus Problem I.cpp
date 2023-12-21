#include "bits/stdc++.h"
using namespace std;
void solve() {
	int n, a = 1, b = 1;
	bool first = false;
	cin >> n;
	for(int k = n; k > 0; ) {
		if(first) {
			for(int j = 0; a + 2 * b * j <= n; ++j) cout << a + 2 * b * j << ' ';
			first = k % 2 == 0;
			a += b;
			k /= 2;
		} else {
			for(int j = 0; a + b + 2 * b * j <= n; ++j) cout << a + b + 2 * b * j << ' ';
			first = k % 2 != 0;
			k = (k + 1) / 2;
		}
		b <<= 1;
	}
	cout << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
