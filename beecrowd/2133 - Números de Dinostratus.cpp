#include "bits/stdc++.h"
using namespace std;
bool solve(int n) {
	int x = 0, y = 0, z = 0;
	for(int k = 2; k * k <= n; ++k) {
		if(n % k) continue;
		int cnt = 0;
		for(; n % k == 0; n /= k) ++cnt;
		if(cnt >= 8) return true;
		if(cnt > 1) ++x;
		if(cnt >= 5) ++z;
		++y;
	}
	if(n != 1) ++y;
	return x > 1 || y >= 4 || x && y >= 3 || z && y >= 2;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	for(int t = 1; cin >> n; ++t) cout << "Instancia " << t << '\n' << (solve(n) ? "sim\n" : "nao\n") << '\n';
	return 0;
}