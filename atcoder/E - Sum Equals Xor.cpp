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
	const int mod = 1e9 + 7;
	string l;
	int cnt = 0, le = 1;

	cin >> l;

	int n = l.size();

	vector<int> pot(n + 1);
	pot[0] = 1;
	for(int i = 1; i <= n; ++i) pot[i] = 3ll * pot[i - 1] % mod;

	for(int i = 0; i < n; ++i) {
		if(l[i] == '1') {
			cnt = (cnt + (i64)le * pot[n - i - 1]) % mod;
			le <<= 1;
			le %= mod;
		}
	}

	cnt = (cnt + le) % mod;

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
