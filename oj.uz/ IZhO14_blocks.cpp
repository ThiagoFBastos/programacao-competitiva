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
 
const i64 INF = 1e15L;
 
void solve() {
	
	int n, k;
 
	cin >> n >> k;
 
	vector<int> a(n + 1);
	vector<i64> dp(n + 1, INF);
 
	a[0] = 1e9;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	
	dp[0] = 0;
 
	for(int i = 1; i <= k; ++i) {
		vector<int> c;
		vector<i64> cost, pre, val(n + 1, INF);
 
		pre.push_back(INF);
 
		for(int j = 1; j <= n; ++j) {
			i64 x = dp[j - 1];			
			while(!c.empty() && c.back() < a[j]) {
				x = min(x, cost.back());
				c.pop_back();
				pre.pop_back();
				cost.pop_back();
			}
			c.push_back(a[j]);
			pre.push_back(min(pre.back(), x + a[j]));
			cost.push_back(x);		
			val[j] = pre.back();	
		}
 
		swap(dp, val);
	}
 
	cout << dp.back() << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}   
