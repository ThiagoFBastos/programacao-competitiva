#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int N, g = 0;
		cin >> N;
		for(int k = 0; k < N; ++k) {
			int X;
			cin >> X;
			g ^= X & 3;
		}
		if(g) cout << "first\n";
		else cout << "second\n";
	}
	return 0;
}
