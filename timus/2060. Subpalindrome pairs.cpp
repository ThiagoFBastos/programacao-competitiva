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
	string s;
	cin >> s;	

	int l = 0, r = -1, n = s.size();
	vector<int> d1(n, 1), d2(n, 0), lo(n + 1, 0), hi(n + 1, 0);
	i64 cnt = 0;

	for(int i = 0; i < n; ++i) {
		
		if(i <= r) {
			d1[i] = min(d1[l + r - i], r - i + 1);
			d2[i] = min(d2[l + r - i + 1], r - i + 1);
		}
		
		while(i + d1[i] < n && i - d1[i] >= 0 && s[i - d1[i]] == s[i + d1[i]]) ++d1[i];

		--lo[i + 1], ++lo[i - d1[i] + 1];
		++hi[i], --hi[i + d1[i]];
		
		while(i + d2[i] < n && i - d2[i] - 1 >= 0 && s[i - d2[i] - 1] == s[i + d2[i]]) ++d2[i];
		
		++lo[i - d2[i]], --lo[i];
		++hi[i], --hi[i + d2[i]];
		
		if(r < i + d2[i] - 1) l = i - d2[i], r = i + d2[i] - 1;
		if(r < i + d1[i] - 1) l = i - d1[i] + 1, r = i + d1[i] - 1;
	}

	for(int i = 1; i < n; ++i) {
		lo[i] += lo[i - 1];
		hi[i] += hi[i - 1];
		cnt += (i64)hi[i - 1] * lo[i];		
	}

	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}