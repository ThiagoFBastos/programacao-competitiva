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

const int INF = 1e9 + 100;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for(int& v : a) cin >> v;
	reverse(a.begin(), a.end());

	vector<int> p(n + 10, INF);
	int ans = 0;

	for(int v : a) {
		int k = upper_bound(p.begin(), p.end(), v) - p.begin();
		ans = max(ans, k + 1);
		p[k] = v;
	}

	cout << ans << '\n';
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//cin >> t;
	while(t--) solve();
}
