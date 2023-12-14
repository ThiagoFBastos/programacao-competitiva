#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<i64, int>;
 
const i64 inf = 1e15L;
 
ii cmp(ii a, ii b) {
	if(a.first != b.first) return min(a, b);
	return max(a, b);
}
 
void solve() {
	
	int n;
 
	cin >> n;
 
   	vector<ii> dp(n, ii(inf, 0)), S(n + 2, ii(inf, 0));
	vector<i64> pre(n + 1, 0);
	
	for(int i = 1; i <= n; ++i) {
		cin >> pre[i];
		pre[i] += pre[i - 1];
		dp[i - 1] = {pre[i], 0};
	}
 
	for(int i = 0; i < n; ++i) {
		S[i + 1] = cmp(S[i + 1], S[i]);
		dp[i] = cmp(dp[i], make_pair(S[i + 1].first + pre[i + 1], S[i + 1].second));
		++dp[i].second;
		int k = lower_bound(pre.begin(), pre.end(), dp[i].first + pre[i + 1]) - pre.begin() - 1;
		S[k + 1] = cmp(S[k + 1], make_pair(-pre[i + 1], dp[i].second));
	}
 
	cout << dp.back().second << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}    #include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<i64, int>;
 
const i64 inf = 1e15L;
 
ii cmp(ii a, ii b) {
	if(a.first != b.first) return min(a, b);
	return max(a, b);
}
 
void solve() {
	
	int n;
 
	cin >> n;
 
   	vector<ii> dp(n, ii(inf, 0)), S(n + 2, ii(inf, 0));
	vector<i64> pre(n + 1, 0);
	
	for(int i = 1; i <= n; ++i) {
		cin >> pre[i];
		pre[i] += pre[i - 1];
		dp[i - 1] = {pre[i], 0};
	}
 
	for(int i = 0; i < n; ++i) {
		S[i + 1] = cmp(S[i + 1], S[i]);
		dp[i] = cmp(dp[i], make_pair(S[i + 1].first + pre[i + 1], S[i + 1].second));
		++dp[i].second;
		int k = lower_bound(pre.begin(), pre.end(), dp[i].first + pre[i + 1]) - pre.begin() - 1;
		S[k + 1] = cmp(S[k + 1], make_pair(-pre[i + 1], dp[i].second));
	}
 
	cout << dp.back().second << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
