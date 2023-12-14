#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 2000000100
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
i64 dp[20][11][11][2];
 
i64 count_palindrome_free(i64 n) {
	if(n < 0) return 0;
 
	string s = to_string(n);
	int m = s.size();
 
	for(int i = 0; i <= m; ++i)
	for(int j = 0; j <= 10; ++j)
	for(int k = 0; k <= 10; ++k)
	for(int l : {0, 1})
		dp[i][j][k][l] = 0;
 
	dp[0][10][10][1] = 1;
 
	for(int i = 1; i <= m; ++i) {
		int ch = s[i - 1] - '0';
 
		dp[i][10][10][0] = 1;
 
		for(int d1 = 0; d1 <= 10; ++d1) {
			for(int d2 = 0; d2 <= 10; ++d2) {
				for(int c = 0; c < 10; ++c) {
					if(c == d2 || c == d1 || (c == 0 && d2 == 10)) continue;
					if(c < ch) dp[i][d2][c][0] += dp[i - 1][d1][d2][1];
					dp[i][d2][c][0] += dp[i - 1][d1][d2][0];
				}
				if(ch != d1 && ch != d2 && !(ch == 0 && d2 == 10)) dp[i][d2][ch][1] += dp[i - 1][d1][d2][1];
			}
		}
	}
		
	i64 ans = 0;
	
	for(int d1 = 0; d1 <= 10; ++d1)
	for(int d2 = 0; d2 <= 10; ++d2)
		ans += dp[m][d1][d2][0] + dp[m][d1][d2][1];
 
	return ans;	
}
 
void solve() {
	i64 a, b;
	cin >> a >> b;
	cout << count_palindrome_free(b) - count_palindrome_free(a - 1) << '\n';
}	
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
