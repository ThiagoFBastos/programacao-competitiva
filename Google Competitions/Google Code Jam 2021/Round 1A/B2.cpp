#include "bits/stdc++.h"
using namespace std;
const int N = 499001;
bool dp[N];
void solve() {
	int m;
	long long t = 0;
	cin >> m;
	vector<long long> p(m), n(m);
	for(int k = 0; k < N; ++k) dp[k] = false;
	dp[1] = true;
	for(int i = 0; i < m; ++i) {
		cin >> p[i] >> n[i];
		t += n[i];
	}
	if(t > 100) {
		cout << "0\n";
		return;
	}
	for(int k = 0; k < m; ++k) {
		for(int i = 0; i < n[k]; ++i) {
			for(int j = N - 1; j; --j) {
				if(j * p[k] >= N || dp[j * p[k]] || !dp[j]) continue;
				dp[j * p[k]] = true;
			}
		}
	}
	for(int k = N - 1; k >= 0; --k) {
		if(!dp[k]) continue;
		long long s = 0;
		int x = k;
		for(int j = 0; j < m; ++j) {
			int cnt = n[j];
			while(x % p[j] == 0) {
				x /= p[j];
				--cnt;
			}
			s += cnt * p[j];
		}
		if(s == k) {
			cout << s << '\n';
			return;
		}
	}
	cout << "0\n";
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Case #" << k << ": "; 
		solve();
	}
	return 0;
}