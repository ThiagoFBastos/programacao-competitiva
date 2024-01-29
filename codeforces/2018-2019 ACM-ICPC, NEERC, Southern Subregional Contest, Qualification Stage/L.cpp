#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

void solve() {
	int n, _, m, __;

	cin >> n >> _;

	vector<int> a(n);
	int mn = 0;

	for(int& v : a) {
		cin >> v;
		mn = min(mn, v);
	}

	cin >> m >> __;

	vector<int> b(m);

	for(int& v : b) {
		cin >> v;
		mn = min(mn, v);
	}

	for(int& v : a) v -= mn;
	for(int& v : b) v -= mn;
	
	int ans = 2;

	for(int i = 0; i <= 30; ++i) {
		unordered_map<int, array<array<int,2>, 2>> mp;

		mp.reserve(n + m);

		for(int v : a) mp[v & ((1<<i) - 1)][0][(v >> i) & 1] += 1;
		for(int v : b) mp[v & ((1<<i) - 1)][1][(v >> i) & 1] += 1;
		
		for(auto& [_, v] : mp)
			ans = max(ans, max(v[0][0]+v[1][1], v[0][1]+v[1][0]));
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

