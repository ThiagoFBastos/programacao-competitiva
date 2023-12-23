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
	int n, frq[30] = {0};
	cin >> n;
	vector<int> a(n);
	i64 ans = 0;
	for(int& v : a) {
		cin >> v;
		ans += v;
		for(int i = 0; i < 30; ++i) frq[i] += (v >> i) & 1;
	}
	for(int v : a) {
		i64 sum = 0;
		for(int i = 0; i < 30; ++i) {
			if((v >> i) & 1) sum += (n - frq[i] + 0ll) << i;
			else sum += (i64)frq[i] << i;
		}
		ans = max(ans, sum);
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
