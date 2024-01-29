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
	int n, q;

	cin >> n >> q;

	map<int, int> a;
	array<int, 33> cnt;

	cnt.fill(0);

	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		++a[v];
		++cnt[1];
	}

	for(int k = 2; k <= 30; ++k) {
		for(int i = 1; ; ++i) {
			i64 val = 1;
			bool inf = false;
			for(int j = 0; j < k; ++j) {
				val *= i;
				if(val > (1LL << 30)) {
					inf = true;
					break;
				}
			}
			if(inf) break;
			auto it = a.find(val);
			cnt[k] += it->second;
		}	
	}

	while(q--) {
		int r;
		cin >> r;
		if(r > 30) cout << a[1] << '\n';
		else cout << cnt[r] << '\n';
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


