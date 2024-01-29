#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, k;
	cin >> n >> k;
	
	vector<int> on(n + 1, 1);
	int off = 0, ans = 0;
	
	while(k--) {
		int i;
		cin >> i;
		for(int j = 1; j * i <= n; ++j) {
			on[i * j] ^= 1;
			if(on[i * j]) --off;
			else ++off;
		}
		ans = max(ans, off);
	}
	
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


