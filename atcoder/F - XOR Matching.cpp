#include "bits/stdc++.h"
using namespace std;

void solve() {
	int n, k;
	cin >> n >> k;
	if(k > (1 << n) - 1) {
		cout << "-1\n";
		return;
	} else if(k == 0) {
		for(int i = 0; i < (1 << n); ++i) cout << i << ' ';
		for(int i = 0; i < (1 << n); ++i) cout << (1 << n) - i - 1 << ' ';
		cout << '\n';
		return;
	} else if(n == 1) {
		cout << "-1\n";
		return;
	}
	cout << k << ' ';
	for(int i = 1; i < (1 << n); ++i) {
		if(i == k) continue;
		cout << i << ' ';
	}
	cout << k << ' ' << 0 << ' ';
	for(int i = (1 << n) - 1; i; --i) {
		if(i == k) continue;
		cout << i << ' ';
	}
	cout << 0 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
