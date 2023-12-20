#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, long long>;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const long long INF = 2e10 + 1;
	int n, x, w[20], m;
	cin >> n >> x;
	m = 1 << n;
	ii **dp = new ii*[m]; 
	for(int i = 0; i < m; ++i) {
		dp[i] = new ii[n];
		for(int k = 0; k < n; ++k)
			dp[i][k] = make_pair(21, 0LL);
	}
	for(int i = 0; i < n; ++i) {
		cin >> w[i];	
		if(w[i] < x) dp[1 << i][i] = make_pair(0, w[i] + 0LL);
		else dp[1 << i][i] = make_pair(1, 0LL);
	}
	for(int i = 1; i < m; ++i) {
		int p = 1, rides = 21;
		long long weight = INF;
		for(int k = 0; k < n; ++k) {
			if(i & p) {
				if(rides > dp[i][k].first) rides = dp[i][k].first, weight = dp[i][k].second;
				else if(rides == dp[i][k].first) weight = min(weight, dp[i][k].second);
			}
			p <<= 1;
		}
		p = 1;
		for(int k = 0; k < n; ++k) {
			if(!(i & p)) {
				int mask = i | p;
				long long W = weight + w[k];
				if(dp[mask][k].first > rides) {
					if(W > x && dp[mask][k].first == rides + 1)
						dp[mask][k].second = min(dp[mask][k].second, 0LL + w[k]);
					else {
						dp[mask][k] = make_pair(rides, W);
						if(W > x) {
							++dp[mask][k].first;
							dp[mask][k].second = w[k];
						}
						else if(W == x) {
							++dp[mask][k].first;
							dp[mask][k].second = 0;
						}
					}
				}
				else if(dp[mask][k].first == rides)
					dp[mask][k].second = min(dp[mask][k].second, W);
			}
			p <<= 1;
		}
	}
	int rides = 21;
	for(int i = 0; i < n; ++i) {
		if(dp[m - 1][i].second) ++dp[m - 1][i].first;
		rides = min(rides, dp[m - 1][i].first);
	}
	cout << rides << '\n';
	return 0;
}
