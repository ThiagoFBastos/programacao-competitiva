#include "bits/stdc++.h"
using namespace std;
vector<long long> bit[2];
int n;
void upd(int x, int y, int v) {
	for(; y <= n; y += y & -y) bit[x][y] += v; 
}
long long query(int x, int y) {
	long long ans = 0;
	for(; y > 0; y -= y & -y) ans += bit[x][y];
	return ans;
}
void solve() {
	cin >> n;
	for(int i = 0; i < 2; ++i) bit[i].assign(n + 1, 0);
	long long ans = 0;
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		ans += query(1, n) - query(1, a);
		upd(1, a,  i - query(0, a)); 
		upd(0, a, 1);
	}
	cout << ans << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}