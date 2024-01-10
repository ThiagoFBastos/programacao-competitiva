#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int l, r;

	cin >> l >> r;

	vector<int> mobius(r + 1, -1), fac(r + 1, 0);

	for(int k = 2; k <= r; ++k) {
		if(!fac[k]) {
			for(int i = k; i <= r; i += k) {
				fac[i] = k;
				mobius[i] *= -1;
			}
			if((i64)k * k <= r) {
				int j = k * k;
				for(int i = j; i <= r; i += j) mobius[i] = 0;
			}
		}
	}

	int n = r - l + 1;

	i64 cnt = (i64)n * n;

	for(int k = 2; k <= r; ++k) {
		int m = r / k - (l - 1) / k;
		cnt -= (i64)mobius[k] * m * m;
	}

	for(int k = l; k <= r; ++k) {
		vector<int> g {1};
		for(int i = k; i > 1; ) {
			int p = fac[i], sz = g.size();
			i64 P = 1;
			while(i % p == 0) {
				P *= p;
				i /= p;
				for(int j = 0; j < sz; ++j) g.push_back(g[j] * P);
			}
		}
		for(int x : g) {
			if(x == 1 || x < l) continue;
			++cnt;
			cnt += x != k;
		}
	}

	cout << (i64)n * n - cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

