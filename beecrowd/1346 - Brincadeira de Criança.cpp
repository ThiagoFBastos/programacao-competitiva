#pragma GCC optimize("O3", "unroll-loops")

#include "bits/stdc++.h"

using namespace std;

const int N = 4e5 + 1, K = 402;
bitset<N> pre[K], suf[K];
int X[400], Y[400];

void solve() {
	int n, soma = 0;
	
	cin >> n;
	
	if(!n) exit(0);
	
	pre[0].reset();
	suf[n + 1].reset();
	
	pre[0][0] = suf[n + 1][0] = 1;
	
	for(int i = 0; i < n; ++i) {
		cin >> X[i] >> Y[i];
		if(X[i] > Y[i]) swap(X[i], Y[i]);
		soma += X[i] + Y[i];
		pre[i + 1] = (pre[i] << X[i]) | (pre[i] << Y[i]);
	}
	
	if((~soma & 1) && pre[n][soma / 2]) {
		cout << soma / 2 << " discard none\n";
		return;
	}
	
	for(int i = n; i; --i) suf[i] = (suf[i + 1] << X[i - 1]) | (suf[i + 1] << Y[i - 1]);
	
	auto ans = make_tuple(-1, -1001, -1001);
	
	for(int i = 0; i < n; ++i) {
		int v = soma - X[i] - Y[i];
		if((v & 1) || v / 2 < get<0>(ans)) continue;
		v /= 2;
		for(int k = 0; k <= v; ++k) {
			if(pre[i][k] && suf[i + 2][v - k]) {
				ans = max(ans, make_tuple(v, -X[i], -Y[i]));
				break;
			}
		}
	}

	auto [a, b, c] = ans;
	
	if(a < 0) {
		cout << "impossible\n";
		return;
	}
	
	cout << a << " discard " << -b << ' ' << -c << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}