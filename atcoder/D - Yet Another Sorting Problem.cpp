#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

void solve() {	
	int n, m, L = 0, R = 0, swaps = 0;
	cin >> n >> m;
	
	vector<int> g(1 + n + m);
	vector<bool> seen(1 + n + m, false);
	
	for(int i = 1; i <= n + m; ++i) cin >> g[i];
	
	for(int i = 1; i <= n + m; ++i) {
		if(seen[i]) continue;
		int x = 0, y = n + m + 1, z = 0;
		for(int v = i; !seen[v]; v = g[v]) {
			seen[v] = true;
			x = max(x, v);
			y = min(y, v);
			++z;
		}
		swaps += z - 1;
		if(z > 1) {
			if(y > n) ++R;
			else if(x <= n) ++L;
		}
	}
	swaps += 2 * max(L, R);
	cout << swaps << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}s
