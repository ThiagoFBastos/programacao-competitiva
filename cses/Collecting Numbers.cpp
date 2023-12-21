#include "bits/stdc++.h"
using namespace std;
struct BIT {
	vector<int> bit;
};
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> p(n + 1);
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		p[a] = i;
	}
	int cnt = 1;
	for(int i = 2; i <= n; ++i) cnt += p[i] < p[i - 1];
	cout << cnt << '\n';
	return 0;
}
