#pragma GCC target("popcnt")
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 3000;
const int B = 60;

string a[N];
bitset<B> adj[N];

void solve() {
	int n;

	cin >> n;

	for(int i = 0; i < n; ++i) cin >> a[i];

	i64 cnt = 0;
	
	for(int l = 0; l < n; l += B) {
		int r = min(n, l + B);

		for(int i = 0; i < n; ++i) {
			adj[i].reset();
			for(int j = l; j < r; ++j)
				adj[i][j] = a[i][j] - '0';
		}

		for(int i = 0; i < n; ++i) {
			bitset<B> S = adj[i];
			for(int j = 0; j < n; ++j) if(a[i][j] == '1') cnt += (S & adj[j]).count();
		}
	}

	cout << cnt / 6 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
