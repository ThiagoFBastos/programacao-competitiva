#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	array<int, 26> cnt, dx, ok, k;
	int r = 0;
	long long ans = 0;
	map<array<int, 26>, int> S;
	cnt.fill(0);
	ok.fill(0);
	k.fill(0);
	for(char c : s) ok[c - 'a'] = 1;
	for(int i = 0; i < 26; ++i) k[i] = ok[i], r += ok[i];
	++S[cnt];
	for(char c : s) {
		r -= ok[c - 'a'];
		ok[c - 'a'] = 0;
		++cnt[c - 'a'];
		for(int i = 0; i < 26; ++i) {
			if(k[i]) dx[i] = cnt[i] - cnt[s[0] - 'a'];
			else dx[i] = 0;
		}
		if(r == 0) {
			auto t = S.find(dx);
			if(t != S.end()) ans += t->second;
		}
		++S[dx];
	}
	cout << ans << '\n';
	return 0;
}
