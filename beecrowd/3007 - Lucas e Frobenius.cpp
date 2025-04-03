#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int N = 1e6;
	int t, p[10];
	bitset<N + 1> S;
	cin >> t;
	while(t--) {
		int n, m = 1e6 + 1;
		cin >> n;
		for(int i = 0; i < n; ++i) cin >> p[i];
		sort(p, p + n);
		for(int i = 0; i < n; ++i) {
			for(int k = i + 1; k < n; ++k) {
				if(__gcd(p[i], p[k]) == 1)
					m = min(m, p[i] * p[k] - p[i] - p[k]);
			}
		}
		if(m > 1e6) 
			cout << -1 << '\n';
		else {
			S.reset();
			S[0] = 1;
			for(int k = 1; k <= m; ++k)
				for(int i = 0; i < n && k - p[i] >= 0; ++i)
					S[k] = S[k] | S[k - p[i]];
			int k = m;
			while(k && S[k]) --k;
			cout << k << '\n';
		}
	}
	return 0;
}