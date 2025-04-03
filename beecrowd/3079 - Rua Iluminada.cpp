#include "bits/stdc++.h"

using namespace std;

void solve() {
	int n, m, k = numeric_limits<int> :: max();
	cin >> n >> m;
	
	vector<int> a(n + 1);
	a[n] = m + 1;
	for(int i = 0; i < n; ++i) cin >> a[i];
	for(int i = 2; i <= n; ++i) k = min(k, a[i] - a[i - 2]);
	
	vector<int> L(2 * n), R(2 * n);
	
	for(int i = k; i; --i) {
		bool ok = false;
		int m = 0, k = 0, j = 0, o = 0;
		
		for(int j = 0; j < n; ++j) {
			if(a[j + 1] - a[j] >= i) {
				L[m] = 0, R[m++] = i - 1;
				continue;
			}
			
			int lo = a[j] % i, hi = (a[j + 1] - 1) % i;
			
			if(lo <= hi) L[m] = lo, R[m++] = hi;
			else L[m] = 0, R[m++] = hi, L[m] = lo, R[m++] = i - 1;
		}
		
		sort(L.begin(), L.begin() + m);
		sort(R.begin(), R.begin() + m);
		
		while(k < m && j < m) {
			if(L[k] <= R[j]) ++k, ++o;
			else --o, ++j;
			if(o == n) {
				ok = true;
				break;
			}
		}
		
		if(ok) {
			cout << i << '\n';
			break;
		}
	}
}
	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}