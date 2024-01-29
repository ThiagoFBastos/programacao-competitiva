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

const int N = 700, inf = 1e9;

int dp[N][N];

vector<int> z_function(string& s) {
    int n = (int) s.length();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if(i <= r) z[i] = min (r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

bool has_period(string& s, vector<int>& z, int k) {
	int n = s.size(); 
	for(int i = k; i < n; i += k) if(z[i] != n - i) return false;
	return true;
}

int periodo(string& s) {
	int n = s.size();
	
	auto z = z_function(s);
	int ans = n;
	
	for(int k = 1; k * k <= n; ++k) {
		if(n % k) continue;
		if(has_period(s, z, k)) ans = min(ans, k);
		if(k * k != n && has_period(s, z, n / k)) ans = min(ans, n / k);
	}
	
	return ans;
}

void solve() {
	int n;
	string s;
	cin >> n >> s;
	
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) dp[i][j] = inf;
		dp[i][i] = 1;
	}
	
	for(int l = 2; l <= n; ++l) {
		for(int i = 0; i + l - 1 < n; ++i) {
			int j = i + l - 1;
			for(int k = i; k < j; ++k) dp[i][j] = min(dp[i][k] + dp[k + 1][j], dp[i][j]);
			string _s = s.substr(i, j - i + 1);
			int p = periodo(_s);
			dp[i][j] = min(dp[i][j], dp[i][i + p - 1]);
		}
	}
	
	cout << dp[0][n - 1] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


