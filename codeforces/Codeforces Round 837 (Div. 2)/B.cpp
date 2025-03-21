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

void solve() {
	int n, m;

	cin >> n >> m;

	vector<bool> inQueue(n, false);
	vector<vector<int>> adj(n);
	int bad = 0;

	for(int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		--x, --y;
		adj[x].pb(y); adj[y].pb(x);
	}

	i64 pairs = 0;

	for(int i = 0, lo = 0; i < n; ++i) {
		inQueue[i] = true;
		for(int k : adj[i]) if(inQueue[k]) ++bad;
		while(lo < i && bad > 0) {
			for(int k : adj[lo]) if(inQueue[k]) --bad;
			inQueue[lo++] = false;
		}
		pairs += i - lo + 1;
	}

	cout << pairs << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
