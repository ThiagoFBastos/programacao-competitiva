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

const int N = 2e5 + 10, K = 18;

i64 sp[K][N];

i64 query(int l, int r) {
	if(l > r) return -INFLL;
	int k = 31 - __builtin_clz(r - l + 1);
	return max(sp[k][l], sp[k][r - (1 << k) + 1]);
}

void solve() {
	int n, k, x;

	cin >> n >> k >> x;

	vector<int> a(n);

	for(int& v : a) cin >> v;

	vector<i64> pref(n + 1, 0);

	for(int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + a[i - 1];

	int lg = 32 - __builtin_clz(n + 1);

	i64 best = 0;

	for(int i = 0; i <= n; ++i) sp[0][i] = pref[i] - (i64)x * i;

	for(int i = 1; i < lg; ++i)
		for(int j = 0; j + (1 << i) <= n + 1; ++j)
			sp[i][j] = max(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);

	if(k == 0) {
		i64 sum = 0;
		for(int v : a) {
			sum += v - x;
			best = max(best, sum);
			sum = max(0ll, sum);
		}
	} else if(x >= 0) {
		for(int i = 0; i < n; ++i) {
			for(int j = 1; j <= k && i + j <= n; ++j) {
				i64 sum = -pref[i] + (i64)x * j + query(i + j + 1, n) + (i64)x * (i + j);
				best = max(best, sum);
				best = max(best, pref[i + j] - pref[i] + (i64)x * j);
			}
		}
	} else {
		for(int i = 0; i < n; ++i) {
			best = max(best, query(i + 1, min(n, i + n - k)) - pref[i] + (i64)x * i);
			if(i + n - k < n) {
				i64 p = (n - k + 0ll) * -x;
				for(int j = i + n - k; j < n; ++j) {
					p += x;
					best = max(best, pref[j + 1] - pref[i] + p); 
				}
			}
		}
	}
	
	cout << best << '\n';
}

int main() {
	
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
