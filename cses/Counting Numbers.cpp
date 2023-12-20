#include "bits/stdc++.h"
using namespace std;
long long cnt[20][10], ok[20], p[19];
long long solve(long long k) {
	if(k == -1) return 0;
	else if(k == 0) return 1;
	string x = to_string(k);
	ok[0] = 1;
	for(int i = 1; i < int(x.size()); ++i) ok[i] = ok[i - 1] && x[i] != x[i - 1];
	for(int i = 0; i <= 9; ++i) cnt[0][i] = i && i <= x[0] - '0';
	for(int i = 1; i < int(x.size()); ++i) {
		long long t = accumulate(cnt[i - 1], cnt[i - 1] + 10, 0LL);
		for(int j = 0; j <= 9; ++j) cnt[i][j] = j <= x[i] - '0' ? t - cnt[i - 1][j] : t - cnt[i - 1][j] - (x[i - 1] != j + '0' && ok[i - 1]);
	}
	return accumulate(cnt[int(x.size()) - 1], cnt[int(x.size()) - 1] + 10, 0LL) + solve(p[int(x.size()) - 1] - 1);
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long a, b;
	cin >> a >> b;
	p[0] = 1;
	for(int i = 1; i <= 18; ++i) p[i] = 10 * p[i - 1];
	cout << solve(b) - solve(a - 1) << '\n';
	return 0;
}
