#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

i64 wrong[13], dp[2][1 << 12], fat[13];

void solve() {
	int n;
	cin >> n;
	
	if(wrong[n] == -1) {

		memset(dp[0], 0, sizeof dp[0]);
		
		dp[0][(1 << n) - 1] = 1;

		for(int i = 0; i < n; ++i) {
			memset(dp[1], 0, sizeof dp[1]);
			for(int j = 0; j < (1 << n); ++j) {
				for(int k = j; k; k -= k & -k) {
					if((k & -k) == (1 << i)) continue;
					dp[1][(k & -k) ^ j] += dp[0][j];
				}
			}
			memcpy(dp[0], dp[1], sizeof dp[1]);
		}

		wrong[n] = dp[0][0];
	}

	cout << wrong[n] << '/' << fat[n] << '\n';
}

int main() {

	fat[0] = 1;
	for(int i = 1; i <= 12; ++i) fat[i] = i * fat[i - 1];
	memset(wrong, -1, sizeof wrong);

    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}

