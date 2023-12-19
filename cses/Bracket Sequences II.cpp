#include "bits/stdc++.h"
using namespace std;
void solve() {
	const int mod = 1e9 + 7;
	int n, pre = 0;
	string str;
	cin >> n >> str;
	if(n % 2) {
		cout << "0\n";
		return;
	}
	for(char ch : str) {
		if(ch == '(') ++pre;
		else if(--pre < 0) {
			cout << "0\n";
			return;
		}
	}
	if(pre > n / 2) {
		cout << "0\n";
		return;
	}
	vector<long long> fat(2 * n + 1), inv(2 * n + 1), invfat(2 * n + 1);
	for(int k = 0; k < 2; ++k) fat[k] = inv[k] = invfat[k] = 1;
	for(int k = 2; k <= 2 * n; ++k) {
		fat[k] = k * fat[k - 1] % mod;
		inv[k] = -(mod / k) * inv[mod % k] % mod;
		invfat[k] = inv[k] * invfat[k - 1] % mod;
	}
	auto C = [&fat, &invfat](int n, int k) {
		return fat[n] * invfat[n - k] % mod * invfat[k] % mod;
	};
	n -= size(str);
	int L = (n - pre) / 2, U = pre + (n - pre) / 2;
	if(L == 0) cout << "1\n";
	else cout << ((C(L + U, L) - C(L + U, L - 1)) % mod + mod) % mod << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
