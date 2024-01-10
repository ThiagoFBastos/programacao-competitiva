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

const int inf = 1e9, N = 11, K = 1e3 + 10;

int cnt[N][K];

void solve() {
	int h, w, x, v = INT_MAX;

	cin >> h >> w >> x;

	for(int i = 1; i <= h; ++i) {
		string s;
		cin >> s;
		for(int j = 0; j < w; ++j) {
			cnt[i][j] = cnt[i - 1][j];
			if(s[j] == '1') ++cnt[i][j];
		}
	}

	for(int i = 0; i < (1 << h); ++i) {
		int ans = 0, lo = 0;
		vector<ii> rows;
		bool ok = true;

		for(int j = 0; j < h; ++j) {
			if(i & 1 << j) {
				rows.emplace_back(lo, j);
				lo = j + 1;
			}
		}

		if(lo < h) rows.emplace_back(lo, h - 1);
	
		for(auto [l, r] : rows) {
			for(int j = 0; j < w; ++j) {
				if(cnt[r + 1][j] - cnt[l][j] > x) {
					ok = false;
					break;
				}
			}
		}

		if(!ok) continue;
		

		ans = (int)rows.size() - 1;

		vector<int> f(rows.size(), 0);

		for(int j = 0; j < w; ++j) {
			bool flag = false;
			for(int k = 0; k < (int)rows.size(); ++k) {
				auto [l, r] = rows[k];
				f[k] += cnt[r + 1][j] - cnt[l][j];
				if(f[k] > x) {
					flag = true;
					break;
				}
			}
			if(flag) {
				++ans;
				for(int k = 0; k < (int)rows.size(); ++k) {
					auto [l, r] = rows[k];
					f[k] = cnt[r + 1][j] - cnt[l][j];
				}
			}
		}


		v = min(v, ans);		
	}

	cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
