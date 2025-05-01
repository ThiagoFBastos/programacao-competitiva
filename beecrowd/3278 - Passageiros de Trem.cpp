#include "bits/stdc++.h"
using namespace std;
void solve() {
	int c, n, a[3];
	auto t = 0LL;
	bool flag = true;
	cin >> c >> n;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < 3; ++j) cin >> a[j];
		t -= a[0];
		if(t < 0) flag = false;
		t += a[1];
		if(t > c || a[2] && t < c) flag = false;
	}
	if(t) flag = false;
	cout << (flag ? "possible\n" : "impossible\n");
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}