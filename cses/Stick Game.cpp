#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k, p[100];
	cin >> n >> k;
	for(int i = 0; i < k; ++i)
		cin >> p[i];
	sort(p, p + k);
	string win(n + 1, 'L');
	win[0] = 'L';
	for(int i = 1; i <= n; ++i) {
		bool ok = false;
		for(int j = 0; j < k && p[j] <= i; ++j) {
			if(win[i - p[j]] == 'L') {
				ok = true;
				break;
			}
		}
		if(ok) win[i] = 'W';
	}
	cout << win.c_str() + 1 << '\n';
	return 0;
}
