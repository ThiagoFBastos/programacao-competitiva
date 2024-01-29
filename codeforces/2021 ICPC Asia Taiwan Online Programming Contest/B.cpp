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
	int n, maxn = 0;

	cin >> n;

	vector<int> a(n);

	for(int& v : a) {
		cin >> v;
		maxn = max(maxn, v);
	}

	vector<int> g(maxn + 1, 0);

	for(int k = 1; k <= maxn; ++k)
		for(int j = 2 * k; j <= maxn; j += k)
			g[j] += k;
	
	for(int x : a) {
		if(g[x] > x) cout << "abundant\n";
		else if(g[x] < x) cout << "deficient\n";
		else cout << "perfect\n";
	}
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	// cin >> t;
	while(t--) solve();
}

