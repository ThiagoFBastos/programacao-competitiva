#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using vi = vector<int>;
using ii = pair<int, int>;
 
int main() {
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
 
	int n;
 
	cin >> n;
 
	vi dp(n + 1);
 
	dp[0] = 0;
 
	for(int k = 1; k <= n; ++k) {
 
		int N = k, d = 0;
 
		while(N) {
 
			d = max(N % 10, d);
			N /= 10;
		}
 
		dp[k] = 1 + dp[k - d];
	}
 
	cout << dp[n] << '\n';
 
	return 0;
}
