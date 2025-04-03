#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
static inline ll count(ll N, int B, string& s);
ll count(ll N, int B, string& s) {
	if(N == 0) return 0;
	string r;
	ll dp[64][10], P = 1;
	bool ok[64] = {false};
	int K = count(s.begin(), s.end(), 'S'), n;
	while(N > 0) {
		r += N % B + '0';
		N /= B;
	}
	reverse(r.begin(), r.end());
	n = r.size();
	if(s[r[0] - '0'] == 'S') 
		ok[0] = true;
	for(int k = 1; k < n; ++k)
		if(s[r[k] - '0'] == 'S') 
			ok[k] = ok[k - 1];
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < B; ++i)
			dp[k][i] = 0;
	for(int k = 1; k <= r[0] - '0'; ++k)
		if(s[k] == 'S')
			dp[0][k] = 1;
	for(int k = 1; k < n; ++k) {
		int d = r[k] - '0';
		for(int i = 0; i <= d; ++i)
			if(s[i] == 'S')
				for(int j = 0; j < B; ++j)
					dp[k][i] += dp[k - 1][j];
		for(int i = d + 1; i < B; ++i)
			if(s[i] == 'S')
				for(int j = 0; j < B; ++j) {
					if(s[j] == 'S') {
						if(j == r[k - 1] - '0')
							dp[k][i] += dp[k - 1][j] - ok[k - 1];
						else
							dp[k][i] += dp[k - 1][j];
					}
				}
	}
	ll ans = 0;
	for(int i = 0; i < B; ++i) 
		ans += dp[n - 1][i];
	for(int i = 0; i < n - 1; ++i) {
		P *= K;
		ans += P;
	}
	if(s[0] == 'S') {
		P = 1;
		for(int i = 0; i < n - 1; ++i) {
			ans -= P;
			P *= K;
		}
	}
	return ans;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll D, H;
	int B;
	string s;
	while(true) {
		cin >> D >> H >> B >> s;
		if(D == -1) break;
		cout << count(H, B, s) - count(D - 1, B, s) << '\n';
	}
	return 0;
}