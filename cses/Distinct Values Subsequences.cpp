#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int MOD = 1e9 + 7;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
	map<int, int> frq;
	int64_t ans = 1;
 
	cin >> n;
 
	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		++frq[v];
	}
 
	for(auto [_, y] : frq)
		ans = ans * (1 + y) % MOD;
 
	ans = (ans + MOD - 1) % MOD;
 
	cout << ans << '\n';
	
	return 0;
}
