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

const int N = 2e5 + 100;
int n, a[N];
i64 h;

int dfs(i64 h, int hi, int g, int b) {
	if(hi < 0) return 0;

	if(h > a[hi]) return 1 + dfs(h + a[hi] / 2, hi - 1, g, b);

	int X = 0;

	if(g) X = max(X, dfs(2 * h, hi, g - 1, b));
	
	if(b) X = max(X, dfs(3 * h, hi, g, b - 1));

	return X;
}

void solve() {
	
	cin >> n >> h;

	for(int i = 0; i < n; ++i) cin >> a[i];

	sort(a, a + n);
	reverse(a, a + n);

	cout << dfs(h, n - 1, 2, 1) << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


