#include "bits/stdc++.h"
 
using namespace std;

using ld = long double;
using ll = long long;

const int N = 16, M = 1 << 15;
const ld INF = 1.5e17L;

ld dp[N][M];
ll sum[M];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	int n, d;

	cin >> n >> d;

	vector<int> w(n);
	ld average = 0;

	for(int& val : w) {
		cin >> val;
		average += val;
	}

	average /= d;

	for(int i = 0; i <= d; ++i)
		for(int j = 0; j < (1 << n); ++j)
			dp[i][j] = INF;

	for(int i = 0; i < (1 << n); ++i) {
		for(int j = 0; j < n; ++j) {
			if(i & (1 << j))
				sum[i] += w[j];
		}
	}

	dp[0][(1 << n) - 1] = 0;

	for(int i = 1; i <= d; ++i) {
		for(int j = 1; j < (1 << n); ++j) {
			for(int k = j; k; k = j & (k - 1)) {
				ld var = (sum[k] - average) * (sum[k] - average);
				dp[i][k ^ j] = min(dp[i][k ^ j], dp[i - 1][j] + var);
			}
		}
	}

	cout.precision(9);
	cout.setf(ios_base :: fixed);

	cout << dp[d][0] / d << '\n';

	return 0;
}