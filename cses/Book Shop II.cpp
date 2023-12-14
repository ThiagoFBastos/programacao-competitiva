#include "bits/stdc++.h"
using namespace std;
const long long inf = 1LL << 40;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, x;
	cin >> n >> x;
	vector<tuple<int, int, int>> a(n);
	vector<long long> dp(x + 1002, -inf); 
	for(int i = 0; i < n; ++i) cin >> get<0>(a[i]);
	for(int i = 0; i < n; ++i) cin >> get<1>(a[i]);
	for(int i = 0; i < n; ++i) cin >> get<2>(a[i]);
	dp[0] = 0;
	for(auto [hi, si, ki] : a) {
		for(int i = 0; i <= min(x, hi - 1); ++i) {
			int inc = 0;
			deque<pair<long long, int>> S;
			for(int k = i; k <= x; k += hi) {
				long long F = dp[k];
				while(!S.empty() && S[0].second <= k) S.pop_front();
				if(!S.empty()) dp[k] = max(dp[k], S[0].first + inc);
				if(F != -inf) {
					int j = k + hi * min((x - k) / hi, ki);
					while(!S.empty() && S.back().first <= F - inc) S.pop_back();
					S.push_back({F - inc, j + hi});
				}
				inc += si;
			}
		}
	}
	cout << *max_element(dp.begin(), dp.begin() + x + 1) << '\n';
	return 0;
}
