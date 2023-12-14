#include "bits/stdc++.h"
using namespace std;
vector<int> subsets(vector<int>& a, int k) {
	vector<int> cnt(1 << k, 0);
	for(int x : a) ++cnt[x];
	for(int i = 0; i < k; ++i)
	for(int j = 0; j < (1 << k); ++j)
		if(j & 1 << i)
			cnt[j] += cnt[j ^ 1 << i];
	return cnt;
}
void solve() {
	int n, k = 0;
	cin >> n;
	vector<int> a(n), b(n);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		k = max(k, 32 - __builtin_clz(a[i]));
	}
	for(int i = 0; i < n; ++i) b[i] = ~a[i] & ((1 << k) - 1);
	auto A = subsets(a, k);
	auto B = subsets(b, k);
	for(int x : a) cout << A[x] << ' ' << B[~x & ((1 << k) - 1)] << ' ' << n - A[~x & ((1 << k) - 1)] << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
