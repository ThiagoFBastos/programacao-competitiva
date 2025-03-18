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

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<i64> uid(0, 1ll << 62);

const int N = 2e5 + 100;

i64 ps[N][5];

void solve() {

	int n;

	cin >> n;

	vector<int> a(n);

	for(int i = 0; i <= n; ++i)
		for(int j = 0; j < 5; ++j)
			ps[i][j] = 0;

	for(int& v : a) cin >> v;
	for(int i = 0; i < n; ++i) {
		int b;
		cin >> b;
		if(a[i] <= b) continue;
		for(int j = 0; j < 5; ++j) {
			i64 x = uid(rng);
			ps[a[i]][j] ^= x; 
			ps[b][j] ^= x;
		}
	}

	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < 5; ++j)
			ps[i][j] ^= ps[i - 1][j];

	vector<int> v;

	for(int k = 1; k <= n; ++k) {
		bool good = true;
		for(int i = 0; i < 5; ++i) {
			for(int j = 0; j <= n; j += k) {
				int l = j + 1, r = min(n, j + k);
				good = good && (ps[r][i] ^ ps[max(0, l - 1)][i]) == 0;
			}	
		}
		if(good) v.pb(k);
	}
	
	cout << size(v) << '\n';
	for(int x : v) cout << x << ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
