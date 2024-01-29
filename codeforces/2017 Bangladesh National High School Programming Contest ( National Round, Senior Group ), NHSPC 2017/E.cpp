#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n;
	i64 ans = 0;

	cin >> n;

	map<int, int> frq;

	vector<int> a(n);

	for(int& v : a) {
		cin >> v;
		++frq[v];
	}

	for(int v : a) ans += n - frq[v];

	ans /= 2;

	if((int)frq.size() != n) ++ans;

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
 
