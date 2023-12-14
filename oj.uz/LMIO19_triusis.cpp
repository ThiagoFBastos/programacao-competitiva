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
 
int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	int n, m;
 
	cin >> n >> m;
 
	vector<int> h(n + 1, 0), coords(n + 1), bit(n + 2, INF);
	
	for(int i = 1; i <= n; ++i) cin >> h[i];
		
	for(int i = 0; i <= n; ++i) coords[i] = h[i] - m * i;
 
	sort(all(coords));
 
	auto get = [&](int x) {
		int k = lower_bound(all(coords), x) - coords.begin();
		return (int)coords.size() - k - 1;
	};
 
	auto upd = [&](int k, int x) {
		for(++k; k <= (int)coords.size(); k += k & -k) bit[k] = min(bit[k], x);
	};
 
	auto query = [&](int k) {
		int ans = INF;
		for(++k; k > 0; k -= k & -k) ans = min(ans, bit[k]);
		return ans;
	};
 
/*
		 0	   1         1         1     0
		hi	hi + m    hi + 2m   hi + 3m  hj
 
		hj <= hi + m * (j - i) 
		hj - mj <= hi - mi
*/
 
	upd(get(0), 0);
 
	int ans = n;
 
	for(int i = 1; i <= n; ++i) {
		int x = get(h[i] - i * m);
		int cnt = query(x) + i - 1;
		upd(x, cnt - i);
		ans = min(ans, cnt + n - i);
	}
 
	cout << ans << '\n';
	
	return 0;
}
