#include "bits/stdc++.h"
using namespace std;
 
void solve(int n, int a, int b, int c) {
	if(n > 0) {
		solve(n - 1, a, c, b);
		cout << a << ' ' << c << '\n';
		solve(n - 1, b, a, c);
	}
}
 
void solve() {
	int n;
	cin >> n;
	cout << (1 << n) - 1 << '\n';	
	solve(n, 1, 2, 3);
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
