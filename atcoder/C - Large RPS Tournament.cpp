#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 101;

char dp[N][N];
int n, k, mod[N];
string s;

char who(char a, char b) {
	if((a=='R'&&b=='S')||(b=='R'&&a=='S')) return 'R';
	if((a=='P'&&b=='R')||(b=='P'&&a=='R')) return 'P';
	if((a=='S'&&b=='P')||(b=='S'&&a=='P')) return 'S';
	return a;
}

char DP(int k, int l) {
	if(dp[k][l] != '\0') return dp[k][l];
	else if(k == 0) return dp[k][l] = s[l];
	return dp[k][l] = who(DP(k - 1, l), DP(k - 1, (l + mod[k - 1]) % n));
}

void solve() {

	cin >> n >> k >> s;

	mod[0] = 1;
	for(int i = 1; i <= k; ++i) mod[i] = 2 * mod[i - 1] % n;

	cout << DP(k, 0) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 s
