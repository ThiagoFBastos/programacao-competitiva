#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 18;
 
int dp[1 << N];
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
 
	int n;
 
	cin >> n;
 
	for(int i = 0; i < n; ++i) {
		int x;
 
		cin >> x;
 
		dp[i] = x;
	}
 
	for(int i = 0; (1 << i) <= n; ++i) {
		for(int j = 0; j < n; ++j) {
			if((j >> i) & 1)
				dp[j] ^= dp[j ^ (1 << i)];
		}
	}
 
	for(int i = 0; i < n; ++i) cout << dp[i] << ' ';
 
	cout << '\n';
 
	return 0;
}
