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

using evento = tuple<int, int, int, int, int>;

const int inf = 1e9;

template<class T>
struct BIT {
	vector<T> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};

void solve() {
	int n, d;

	cin >> n >> d;

	vector<ii> pe(n);
	vector<tuple<int, int, int>> p(n);
	vector<int> cnt(n, -1);
	vector<evento> e(2 * n);
	int cur = 0;
	BIT<int> bit(n + 1);

	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;

		x += y;
		y = x - 2 * y;

		p[i] = {x, y, i};
		pe[i] = {y, i};

		e[2 * i] = {x - d, 0, y - d, y + d, i};
		e[2 * i + 1] = {x + d + 1, 1, y - d, y + d, i};
	}

	p.emplace_back(inf, inf, n);
	pe.emplace_back(inf, n);
	sort(p.begin(), p.end());
	sort(e.begin(), e.end());
	sort(pe.begin(), pe.end());
	
	for(int i = 0; i <= n; ++i) {
		auto [x, y, z] = p[i];
		while(cur < 2 * n && get<0>(e[cur]) <= x) {
			auto [x, tipo, y0, y1, id] = e[cur++];
			int lo = lower_bound(pe.begin(), pe.end(), make_pair(y0, -inf)) - pe.begin();
			int hi = lower_bound(pe.begin(), pe.end(), make_pair(y1, inf)) - pe.begin() - 1;
			int t = bit.query(lo, hi);
			if(tipo == 0) cnt[id] -= t;
			else cnt[id] += t;
		}
		int k = lower_bound(pe.begin(), pe.end(), make_pair(y, z)) - pe.begin();
		bit.upd(k, 1);
	}

	for(int i = 0; i < n; ++i) cout << cnt[i] << ' ';
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