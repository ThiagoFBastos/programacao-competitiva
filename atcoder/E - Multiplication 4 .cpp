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

const int mod = 1e9 + 7;

i64 max_product(vector<int>& v, int k) {
	int i = 0, j = 0;
	vector<i64> a, b;
	i64 ans = 1;

	for(int x : v) {
		if(x >= 0) a.push_back(x);
		else if(x < 0) b.push_back(-x);
	}

	int n = a.size(), m = b.size();

	sort(a.rbegin(), a.rend());
	sort(b.rbegin(), b.rend());

	if(k % 2) {
		ans = a[0];
		++i;
		--k;
	}

	while(k >= 2 && i + 2 <= n && j + 2 <= m) {
		k -= 2;
		if(a[i] * a[i + 1] > b[j] * b[j + 1]) {
			ans = ans * a[i] % mod * a[i + 1] % mod;
			i += 2;
		} else {
			ans = ans * b[j] % mod * b[j + 1] % mod;
			j += 2;
		}
	}

	while(k >= 2 && j + 2 <= m) {
		k -= 2;
		ans = ans * b[j] % mod * b[j + 1] % mod;
		j += 2;
	}

	while(k > 0 && i < n) {
		--k;
		ans = ans * a[i++] % mod;
	}
  
	return (ans + mod) % mod;
}

void solve() {
	
	int n, k;

	cin >> n >> k;

	vector<int> v(n);
	int p = 0, q = 0;
	i64 ans = 1;

	for(int& x : v) {
		cin >> x;
		p += x >= 0;
		q += x < 0;
		if(x >= 0) ans = ans * x % mod;
	}

	if(k == n || k % 2 && n == q) {
		vector<int> y;
		for(int x : v) if(x < 0) y.push_back(x);
		sort(y.rbegin(), y.rend());
		for(int i = 0; i < k - p; ++i) ans = ans * y[i] % mod;
		cout << (ans + mod) % mod << '\n';
		return;
	}

	cout << max_product(v, k) << '\n';
}


int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
