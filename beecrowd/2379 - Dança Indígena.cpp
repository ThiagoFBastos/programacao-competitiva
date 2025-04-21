#include "bits/stdc++.h"
using namespace std;
int mod(int a, int b) {
	if(a < 0) return a + b;
	else if(a >= b) return a - b;
	return a;
}
void solve() {
	int n, e, ans = INT_MAX;
	cin >> n >> e;
	vector<int> pos(e), sig(e), S(e), a(e);
	for(int i = 0; i < e; ++i) {
		cin >> pos[i] >> sig[i];
		S[i] = --pos[i];	
	}
	sort(S.begin(), S.end());
	for(int i = 0; i < e; ++i) {
		int passos = mod(sig[0] * (pos[i] - pos[0]), n);
		a[0] = pos[i];
		for(int j = 1; j < e; ++j) a[j] = mod(pos[j] + passos * sig[j], n);
		sort(a.begin(), a.end());
		if(a == S) ans = min(ans, passos == 0 ? n : passos);
	}
	cout << ans << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}