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

int dp[1 << 16][26];

void solve() {
	int n;

	cin >> n;

	vector<string> s(n);

	for(auto& w : s) cin >> w;

	for(int j = 0; j < 26; ++j) dp[0][j] = 2;

	for(int i = 1; i < (1 << n); ++i) {
		for(int j = 0; j < 26; ++j) {
			bool flag = false;
			for(int S = i; S; S -= S & -S) {
				int k = __builtin_ctz(S);
				if(s[k].back() != j + 'a') continue;
				flag = flag || dp[i ^ (1 << k)][s[k][0] - 'a'] == 2;			
			}	
			dp[i][j] = flag ? 1 : 2;
		}
	}

	bool flag = false;
	for(int i = 0; i < 26; ++i) flag = flag || dp[(1 << n) - 1][i] == 1;
	cout << (flag ? "First\n" : "Second\n");
}	

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}


