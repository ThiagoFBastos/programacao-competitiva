#include "bits/stdc++.h"
using namespace std;
int n;
long long F(long long k) {
	long long cnt = 0;
	for(int i = 1; i <= n && k >= i; ++i) cnt += min<long long>(n, k / i);
	return cnt;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	long long lo = 1, hi = 1LL * n * n;
	auto k = (hi + 1) / 2;
	while(lo < hi) {
		auto mid = (lo + hi) >> 1;
		if(F(mid) >= k) hi = mid;
		else lo = mid + 1;
	}
	cout << hi << '\n';
	return 0;
}
