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
	int n; 
	i64 x;

	cin >> n >> x;	

	vector<i64> cnt[3];

	for(int k = 0; k < 3; ++k) cnt[k].assign(3 * n + 1, 0);
	for(int k = 1; k <= n; ++k) cnt[0][k] = 1;

	for(int k = 1; k < 3; ++k) {
		for(int i = 1; i <= 3 * n; ++i) {
			int l = max(0, i - n - 1), r = i - 1;	
			cnt[k - 1][i] += cnt[k - 1][i - 1];
			cnt[k][i] += cnt[k - 1][r] - cnt[k - 1][l];
		}
	}

	for(int s = 3; s <= 3 * n; ++s) {
		cnt[2][s] += cnt[2][s - 1];
		if(cnt[2][s] < x) continue;
		x -= cnt[2][s - 1];
		for(int i = 1; i <= n; ++i) {
			if(s - i < 2 || s - i > 2 * n) continue;
			x -= cnt[1][s - i] - cnt[1][s - i - 1];
			if(x <= 0) {
				x += cnt[1][s - i] - cnt[1][s - i - 1];
				for(int j = 1; j <= n; ++j) {
					int k = s - i - j;
					if(k <= 0 || k > n) continue;
					if(--x <= 0) {
						cout << i << ' ' << j << ' ' << k << '\n';
						break;
					}
				}
				break;					
			}
		}			
		break;
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

