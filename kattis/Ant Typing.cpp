#include "bits/stdc++.h"
using namespace std;
void solve() {
	string s;
	int g[10][10] = {{0}}, ans = INT_MAX;
	cin >> s;
	vector<int> p, pos(10);
	for(int i = 1; i <= 9; ++i) p.push_back(i);
	for(int i = 0; i < int(size(s)) - 1; ++i) ++g[s[i] - '0'][s[i + 1] - '0'];
	do {
		for(int i = 0; i < 9; ++i) pos[p[i]] = i;
		int x = 1 + pos[s[0] - '0'];
		for(int i = 1; i <= 9; ++i)
		for(int j = 1; j <= 9; ++j)
			x += (1 + abs(pos[i] - pos[j])) * g[i][j];
		ans = min(ans, x);
	} while(next_permutation(p.begin(), p.end()));
	cout << ans << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}