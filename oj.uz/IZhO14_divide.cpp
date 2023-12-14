#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;
 
const i64 linf = 1e15L;
 
struct BIT {
	vector<i64> bit;
	
	BIT(int n) {
		bit.assign(n + 1, -linf);
	}
	
	void upd(int k, i64 x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] = max(x, bit[k]);
	}
	
	i64 query(int k) {
		i64 ans = -linf;
		for(++k; k > 0; k -= k & -k) ans = max(ans, bit[k]);
		return ans;
	}
};
 
void solve() {
	int n;
 
	cin >> n;
 
	vector<int> x(n + 1, 0);
	vector<i64> g(n + 1, 0), e(n + 1, 0), p;
	BIT bit(n);
	i64 ans = 0;
 
	for(int i = 1; i <= n; ++i) {
		cin >> x[i] >> g[i] >> e[i];	
		ans = max(ans, g[i]);
		g[i] += g[i - 1];
		e[i] += e[i - 1];
		p.emplace_back(e[i] - x[i]);
	}
 
	sort(p.begin(), p.end());
 
	for(int i = 1; i <= n; ++i) {
		int k = lower_bound(p.begin(), p.end(), e[i] - x[i]) - p.begin();
		ans = max(ans, g[i] + bit.query(k));
		k = lower_bound(p.begin(), p.end(), e[i - 1] - x[i]) - p.begin();
		bit.upd(k, -g[i - 1]);
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
