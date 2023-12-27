#include "bits/stdc++.h"
using namespace std;
int find_digit(long long k) {
	long long p = 1, cnt = 0;
	int i;
	for(i = 1; cnt < k; ++i, p *= 10) cnt += 9 * p * i;
	p /= 10, --i, cnt -= 9 * p * i;
	auto x = p - 1 + (k - cnt + i - 1) / i;
	cnt += i * ((k - cnt + i - 1) / i - 1);
	for(int j = 0; j < i - k + cnt; ++j) x /= 10;
	return x % 10;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> q;
	while(q--) {
		long long k;
		cin >> k;
		cout << find_digit(k) << '\n';
	}
	return 0;
}
