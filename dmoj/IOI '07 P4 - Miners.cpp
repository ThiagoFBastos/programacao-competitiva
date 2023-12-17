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

const int inf = 1e9, N = 16;

int dp[N][N];

int eval(int x) {
	int cnt[4] = {0};
	
	for(int i = 0; i < 3; ++i) {
		++cnt[x % 4];
		x /= 4;
	}

	int t = 0;
	for(int i = 1; i < 4; ++i) t += !!cnt[i];
	return t;
}

int to(int x, int y) {
	return (4 * x + y) % 16;
}

void solve() {
	int n;
	string s;
	cin >> n >> s;
	
	for(int i = 0; i < N; ++i)
	for(int j = 0; j < N; ++j)
		dp[i][j] = -inf;
	
	dp[0][0] = 0;
	
	for(char ch : s) {
		int a[N][N];
		
		for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
			a[i][j] = -inf;
		
		int z;
		
		if(ch == 'M') z = 1;
		else if(ch == 'F') z = 2;
		else z = 3;
		
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				a[to(i, z)][j] = max(a[to(i, z)][j], dp[i][j] + eval(4 * i + z));
				a[i][to(j, z)] = max(a[i][to(j, z)], dp[i][j] + eval(4 * j + z));
			}
		}
		
		for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
			dp[i][j] = a[i][j];
	}
	
	int ans = 0;
	
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
			ans = max(ans, dp[i][j]);
			
	cout << ans << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}
