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

int n;
vector<int> a, b;

int max_median() {
	vector<int> c(n);
	for(int i = 0; i < n; ++i) c[i] = b[i];
	sort(c.begin(), c.end());
	if(n & 1) return c[n / 2];
	return c[n / 2] + c[n / 2 - 1];
}

int min_median() {
	vector<int> c(n);
	for(int i = 0; i < n; ++i) c[i] = a[i];
	sort(c.begin(), c.end());
	if(n & 1) return c[n / 2];
	return c[n / 2] + c[n / 2 - 1];
}

void solve() {
	cin >> n;
	a.resize(n);
	b.resize(n);
	for(int i = 0; i < n; ++i) cin >> a[i] >> b[i];
	cout << max_median() - min_median() + 1 << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
