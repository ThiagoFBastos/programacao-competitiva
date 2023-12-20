#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 2e5, MAXL = 30;
	int n, q, st[MAXL][MAXN];
	cin >> n >> q;
	for(int i = 0; i < n; ++i) {
		cin >> st[0][i];
		--st[0][i];
	}
	for(int i = 1; i < MAXL; ++i)
		for(int k = 0; k < n; ++k)
			st[i][k] = st[i - 1][st[i - 1][k]];
	while(q--) {
		int x, k, p = 1 << MAXL - 1;
		cin >> x >> k;
		--x;
		if(k == 0)
			cout << 1 + x << '\n';
		else {
			for(int i = MAXL - 1; i >= 0 && k; --i) {
				if(p <= k) {
					k -= p;
					x = st[i][x];
				}
				p >>= 1;
			}
			cout << x + 1 << '\n';
		}
	}
	return 0;
}
