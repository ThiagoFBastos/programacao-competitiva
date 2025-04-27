#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int maxn = 1000;
	int n, m, l, ans = INT_MAX;
	bitset<maxn> mask;
	cin >> n >> m >> l;
	vector<bitset<maxn>> p(n + 1);
	while(l--) {
		int x;
		cin >> x;
		mask[x - 1] = 1;
	}
	for(int k = 1; k <= n; ++k) {
		int l;
		cin >> l;
		while(l--) {
			int x;
			cin >> x;
			p[k][x - 1] = 1;
		}
		p[k] ^= p[k - 1];
		if(!(mask ^ p[k]).count()) 
			ans = min(ans, k);
	}
	for(int k = 1; k <= n; ++k) {
		if(!(mask ^ p[n] ^ p[k]).count())
			ans = min(ans, k + n);	
	}
	cout << (ans == INT_MAX ? -1 : ans) << '\n';
	return 0;
}