#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int fib[40], calls[40];
	fib[0] = 0;
	fib[1] = 1;
	calls[0] = 1;
	calls[1] = 1;
	for(int k = 2; k < 40; ++k) {
		fib[k] = fib[k - 1] + fib[k - 2];
		calls[k] = 1 + calls[k - 1] + calls[k - 2];
	}
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		cout << "fib(" << n << ") = " << calls[n] - 1 << " calls = " << fib[n] << '\n';
	}
	return 0;
}