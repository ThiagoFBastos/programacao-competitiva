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

struct op {
	i64 operator()(i64 a, i64 b) {
		return min(a, b);
	}
};

template<class T, class op>
struct BIT {
	vector<T> bit;
	const T neutral = INFLL;

	BIT() {}

	BIT(int n) {
		bit.assign(n + 1, neutral);
	}
	
	void upd(int k, T x) {	
		for(++k; k < int(bit.size()); k += k & -k) bit[k] = op()(bit[k], x);
	}
	
	T query(int k) {
		T ans = neutral;
		for(++k; k > 0; k -= k & -k) ans = op()(ans, bit[k]);
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return neutral;
		return op()(query(r), -query(l - 1));
	}
};

void solve() {
	int n, m;

	cin >> n >> m;

	vector<ii> a(n), b(m);
	vector<int> coords;
	vector<i64> best(n, INFLL);

	for(auto& [x, y] : a) {
		cin >> x >> y;
		coords.pb(y);
	}

	for(auto& [x, y] : b) {
		cin >> x >> y;
		coords.pb(y);
	}

	sort(all(a));
	sort(all(b));
	sort(all(coords));

	auto get = [&](int y) {
		return lower_bound(all(coords), y) - coords.begin();
	};

	for(int i = 0; i < 2; ++i) {
		BIT<i64, op> b1(n + m), b2(n + m);
		int k = 0, j = 0;

		while(k < n) {
			if(j < m && b[j].fi <= a[k].fi) {
				auto [x, y] = b[j++];
				b1.upd(get(y), -x - y);
				b2.upd(n + m - get(y) - 1, -x + y);
			} else {
				auto [x, y] = a[k];
				i64 d = min(b1.query(get(y)) + x + y, b2.query(n + m - get(y) - 1) + x - y);
				best[k] = min(best[k], d);
				++k;
			}
		}

		for(auto& [x, y] : a) x *= -1;
		for(auto& [x, y] : b) x *= -1;

		reverse(all(a));
		reverse(all(b));
		reverse(all(best));
	}

	cout << accumulate(all(best), 0LL) << '\n';
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

