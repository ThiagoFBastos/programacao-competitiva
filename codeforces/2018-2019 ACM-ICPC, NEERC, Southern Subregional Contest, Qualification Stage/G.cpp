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
	int n;

	cin >> n;

	vector<int> frq(n + 1, 0), seen, unseen, par(n + 1, -1);
	vector<ii> ed;

	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		if(b < n) {
			cout << "NO\n";
			return;
		}
		++frq[a], ++frq[b];
	}

	for(int i = n - 1; i; --i) {
		if(frq[i]) seen.pb(i);
		else unseen.pb(i);
	}

	reverse(all(unseen));

	for(int u : seen) {
		int v = u;
		for(int i = 0; i < frq[u] - 1; ++i) {
			if(unseen.empty() || unseen.back() > u) {
				cout << "NO\n";
				return;
			}		
			int w = unseen.back();
			par[v] = w;
			ed.pb({u, w});
			v = w;
			unseen.pop_back();
		}
	}

	if(!unseen.empty()) {
		cout << "NO\n";
		return;
	}

	for(int i = 1; i < n; ++i) if(par[i] < 0) par[i] = n;
	
	cout << "YES\n";
	for(int i = 1; i < n; ++i) cout << i << ' ' << par[i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

