#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 2e5;
	int n, h[MAXN], t = 0;
	cin >> n;
	for(int k = 0; k < n; ++k)
		h[k] = INT_MAX;
	for(int k = 0; k < n; ++k) {
		int a;
		cin >> a;
		int i = upper_bound(h, h + n, a) - h;
		if(h[i] == INT_MAX) ++t;
		h[i] = a;
	}
	cout << t << '\n';
	return 0;
}
