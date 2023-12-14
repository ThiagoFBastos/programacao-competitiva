#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	long long k;
	cin >> n >> k;
	vector<int> p(n + 1, -1);
	vector<bool> marked(n + 1, false);
	int hi = n, lo = 0;
	while(k > 0) {
		marked[hi] = true;
		if(hi - 1 >= k) {
			p[lo + hi - k] = hi;
			break;
		} else {
			k -= hi - 1;
			p[++lo] = hi--;
		}
	}
	int j = 1;
	for(int i = 1; i <= n; ++i) {
		if(p[i] == -1) {
			while(j <= n && marked[j]) ++j;
			p[i] = j++;
		}
	}
	for(int i = 1; i <= n; ++i) cout << p[i] << ' ';
	cout << '\n';
	return 0;
}
