#include "bits/stdc++.h"

using namespace std;

using ll = long long;

const int mod = 1e9 + 7;

void solve() {
	int n, pos[] = {-1, -1};
	
	string s;
	
	cin >> n >> s;

	int ans = 0;
	
	for(int i = 0; i < n; ++i) {
		char ch = s[i];
		if(ch == 'X' && pos[0] > pos[1]) ans = (ans + (pos[0] + 1LL) * (n - i)) % mod;	
		if(ch == 'O' && pos[1] > pos[0]) ans = (ans + (pos[1] + 1LL) * (n - i)) % mod;
		if(ch == 'O') pos[0] = i;
		else if(ch == 'X') pos[1] = i;
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
 	return 0;
}
