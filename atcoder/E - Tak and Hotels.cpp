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

const int N = 1e5 + 100, K = 17;

int nxt[K][N];

void solve() {
	int n, l, q;

	cin >> n;

	vector<int> x(n);

	for(int& v : x) cin >> v;

	cin >> l;

	for(int i = 0; i < n; ++i)
		nxt[0][i] = upper_bound(all(x), x[i] + l) - x.begin() - 1;

	for(int i = 1; i < K; ++i)
		for(int j = 0; j < n; ++j)
			nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
	
	cin >> q;

	while(q--) {
		int a, b, ans = 1;

		cin >> a >> b;

		--a, --b;

		if(a > b) swap(a, b);

		for(int i = K - 1; i >= 0; --i) {
			if(nxt[i][a] < b) {
				ans += 1 << i;
				a = nxt[i][a];
			}
		}
		
		cout << ans << '\n';
	}
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
