#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvii = vector<vii>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int mod = 1e9 + 7, maxn = 1e5 + 1;

int dp[maxn], a, b, hi, ans = 1;
char n[101], s[maxn];

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> s;
	
	a = strlen(n);
	b = strlen(s);

	dp[b] = 1;
	hi = b;

	for(int k = b - 1; k >= 0; --k) {
		if(s[k] == '0') {
			dp[k] = 0;
			continue;
		}
		if(k + a > b)
			dp[k] = ans;
		else {
			while(hi - k > a) {
				ans -= dp[hi];
				if(ans < 0) 
					ans += mod;
				--hi;
			}
			if(strncmp(s + k, n, a) <= 0)
				dp[k] = ans;
			else {
				ans -= dp[hi--];
				if(ans < 0) ans += mod;
				dp[k] = ans;
			}
		}
		ans += dp[k];
		if(ans >= mod)
			ans -= mod;
	}

	cout << dp[0] << '\n';

	return 0;
}