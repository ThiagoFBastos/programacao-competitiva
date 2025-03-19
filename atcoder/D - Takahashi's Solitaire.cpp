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

	vector<int> a(n);
	i64 sum = 0;

	for(int& v : a) {
		cin >> v;
		sum += v;
	}

	sort(all(a));

	for(int i = 0; i < n; ++i) a.pb(a[i]);

	i64 cur_sum = a.back(), ans = sum - a.back();
	int hi = 2 * n - 1;

	for(int i = 2 * n - 2; i >= 0; --i) {
		int x = (a[i + 1] - a[i] + m) % m;
		if(x <= 1) cur_sum += a[i];
		else cur_sum = a[i], hi = i;
		while(hi - i + 1 > n) cur_sum -= a[hi--];
		ans = min(ans, sum - cur_sum);
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