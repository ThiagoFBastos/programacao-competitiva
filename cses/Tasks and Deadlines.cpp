#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	long long R = 0, S = 0;
	cin >> n;
	vector<int> a(n);
	for(int k = 0; k < n; ++k) {
		int d;
		cin >> a[k] >> d;
		R += d - a[k];
	}
	sort(a.begin(), a.end());
	for(int k = 0; k < n; ++k) {
		R -= S;
		S += a[k];
	}
	cout << R << '\n';
	return 0;
}
