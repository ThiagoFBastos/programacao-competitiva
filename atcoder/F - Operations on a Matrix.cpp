#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

template<class T>
struct BIT {
	vector<T> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};

void solve() {

	int n, m, q;

	cin >> n >> m >> q;

	BIT<i64> bit(m);
	vector<i64> value(n + 1, 0), sub(q, 0), last(n + 1, -1);
	vector<vector<ii>> nxt(q);
	vector<tuple<int, int, int, int>> query(q);
	
	for(int i = 0; i < q; ++i) {
		int t, a, b, c = -1;
		cin >> t >> a >> b;
		if(t == 1) cin >> c;
		if(t == 3 && last[a] != -1) nxt[last[a]].emplace_back(i, b);
		if(t == 2) last[a] = i;
		query[i] = {t, a, b, c};
	}
	
	for(int i = 0; i < q; ++i) {
		auto [t, a, b, c] = query[i];
		if(t == 1) {
			bit.upd(a, c);
			bit.upd(b + 1, -c);
		} else if(t == 2) {
			value[a] = b;
			for(auto [pos, col] : nxt[i]) sub[pos] += bit.query(col);
		} else cout << value[a] + bit.query(b) - sub[i] << '\n';
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
