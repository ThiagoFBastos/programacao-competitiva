#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

int a[2][2], b[2][2], f[2][202];

void solve() {
	
	for(int k = 0; k < 2; ++k)
	for(int i = 0; i < 2; ++i) cin >> a[k][i] >> b[k][i];
	
	for(int k = 0; k < 2; ++k) {
		for(int x = a[k][0]; x <= b[k][0]; ++x) {
			++f[k][x + a[k][1]];
			--f[k][x + b[k][1] + 1];
		}
		for(int x = 1; x <= 200; ++x) f[k][x] += f[k][x - 1];
	}
	
	long long L = 0, R = 0;
	
	for(int x = 1; x <= 200; ++x) {	
		for(int y = 1; y < x; ++y) L += 1LL * f[0][x] * f[1][y];
		for(int y = x + 1; y <= 200; ++y) R += 1LL * f[0][x] * f[1][y];
	}
	
	if(L == R) cout << "Tie" << endl;
	else if(L > R) cout << "Gunnar" << endl;
	else cout << "Emma" << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}