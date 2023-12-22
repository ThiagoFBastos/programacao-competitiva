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

using T = tuple<int, int, int>;

void solve() {
	int n, q;

	cin >> n >> q;

	vector<int> prev(n + 1, -1), nxt(n + 1, -1), a(n);

	for(int& v : a) cin >> v;

	for(int i = n - 1; i >= 0; --i) {
		nxt[i] = prev[a[i]];
		prev[a[i]] = i;
	}

	BIT<int> bit(n);

	for(int i = 0; i < n; ++i) if(prev[a[i]] == i) bit.upd(i, 1);
	
	vector<T> queries(q);
	vector<int> ans(q);

	for(int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		queries[i] = {l - 1, r - 1, i};
	}

	sort(queries.begin(), queries.end());
	
	for(int i = 0, k = 0; i < n && k < q; ++i) {

		for(; k < q; ++k) {
			auto [l, r, j] = queries[k];
			if(l > i) break;
			ans[j] = bit.query(r);
		}

		bit.upd(i, -1);

		if(nxt[i] != -1) bit.upd(nxt[i], 1);
	}

	for(int v : ans) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

