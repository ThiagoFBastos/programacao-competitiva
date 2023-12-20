#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
class Fenwick {
	vi ft;
	int n;
	public:
	Fenwick(int n) {
		this->n = n;
		ft.assign(n + 1, 0);
	}
	int query(int r) {
		int ans {};
		while(r > 0) {
			ans = max(ans, ft[r]);
			r -= r & -r;
		}
		return ans;
	}
	void update(int k, int x) {
		while(k <= n) {
			ft[k] = max(ft[k], x);
			k += k & -k;
		}
	}
};
#define MAXN 200000
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, x[MAXN], y[MAXN];
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> x[i];
		y[i] = x[i];
	}
	sort(y, y + n);
	auto it = unique(y, y + n);
	int m = distance(y, it), ans = 0;
	Fenwick ft(m);
	for(int i = 0; i < n; ++i) {
		int addr = lower_bound(y, y + m, x[i]) - y;
		int l = ft.query(addr) + 1;
		ans = max(ans, l);
		ft.update(addr + 1, l);
	}
	cout << ans << '\n';
	return 0;
} 
