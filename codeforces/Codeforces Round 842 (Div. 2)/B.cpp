#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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
	int n, k;

	cin >> n >> k;
	
	vector<int> a(n), pos(n + 1);
	vector<bool> good(n + 1, true);

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		pos[a[i]] = i;
	}

	for(int i = 2; i <= n; ++i) good[i] = good[i - 1] && pos[i] > pos[i - 1];

	if(good[n]) {
		cout << "0\n";
		return;
	}

	int ans = INF;

	for(int x = 1; x <= n; ++x) if(good[x - 1]) ans = min(ans, (n - x + 1 + k - 1) / k);

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
