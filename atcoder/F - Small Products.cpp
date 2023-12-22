#include "bits/stdc++.h"
using namespace std;

const int mod = 1e9 + 7;

int mod_sum(int x) {
	return x >= mod ? x - mod : x;
}

void solve() {

	int n, k;
	cin >> n >> k;
	
	int m = sqrt(n);
	
	vector<int> a(m + 1, 0), b(m + 1, 0), pa(m + 1), pb(m + 1);	
	
	a[1] = 1;
	
	for(int i = 1; i <= k; ++i) {
	
		pa[0] = pb[0] = 0;
		
		for(int j = 1; j <= m; ++j) {
			pa[j] = mod_sum(pa[j - 1] + a[j]);
			pb[j] = mod_sum(pb[j - 1] + b[j]);
		}
		
		for(int j = 1; j <= m; ++j) {
			a[j] = mod_sum(pa[min(m, n / j)] + mod_sum(pb[m] - pb[j - 1] + mod));
			int L = 1 + max(m, n / (j + 1)), R = n / j;
			if(L <= R) b[j] = pa[j] * (R - L + 1LL) % mod;
		}
	}
	
	int cnt = 0;
	
	for(int i = 1; i <= m; ++i) cnt = mod_sum(cnt + mod_sum(a[i] + b[i]));
	
	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
