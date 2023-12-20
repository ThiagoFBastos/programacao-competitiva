#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
#define f first
#define s second
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using project = tuple<int, int, int>;
bool cmp(project l, project r) {
	return get<1>(l) < get<1>(r);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<project> p(n);
	vector<ll> dp(n);
	for(project& x : p) cin >> get<0>(x) >> get<1>(x) >> get<2>(x);
	sort(p.begin(), p.end(), cmp);
	dp[0] = get<2>(p[0]);
	for(int i = 1; i < n; ++i) {
		int k = upper_bound(p.begin(), p.end(), make_tuple(0, get<0>(p[i]) - 1, 0), cmp) - p.begin() - 1;
		if(k >= 0) dp[i] = get<2>(p[i]) + dp[k];
		else dp[i] = get<2>(p[i]);
		dp[i] = max(dp[i], dp[i - 1]);
	}
	cout << dp[n - 1] << '\n';
	return 0;
} 
