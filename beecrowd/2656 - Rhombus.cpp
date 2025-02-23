#pragma GCC optimize("O3")
#pragma GCC target("mmx", "sse", "sse2", "sse3", "sse4", "avx")

#include "bits/stdc++.h"

using namespace std;


using dat = tuple<int, int, int, int>;
using ii = pair<int, int>;

struct OrderedSet {
	vector<int> bit, P;

	void create() {
		P.resize(unique(P.begin(), P.end()) - P.begin());
		bit.assign(size(P) + 1, 0);
	}
	
	bool empty() {
		return query(size(P)) == 0;
	}
	
	int order_of_key(int x) {
		int k = lower_bound(P.begin(), P.end(), x) - P.begin();
		return query(k);
	}
	
	void insert(int x) {
		int k = lower_bound(P.begin(), P.end(), x) - P.begin();
		upd(k + 1, 1);
	}
	
	void erase(int x) {
		int k = lower_bound(P.begin(), P.end(), x) - P.begin();
		upd(k + 1, -1);
	}
	
	int query(int k) {
		int ans = 0;
		for(; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	void upd(int k, int x) {
		for(; k < int(size(bit)); k += k & -k) bit[k] += x;
	}
};

struct SegTree {
	vector<OrderedSet> st;
	
	SegTree(vector<ii> &p) {
		int n = size(p);
		st.resize(2 * n + 1);
		
		for(int i = 0; i < n; ++i) {
			st[i + n].P.push_back(p[i].second);
			st[i + n].create();
		}
		
		for(int i = n - 1; i; --i) {
			auto& L = st[2 * i].P;
			auto& R = st[2 * i + 1].P;
			auto& src = st[i].P;
			src.resize(size(L) + size(R));
			merge(L.begin(), L.end(), R.begin(), R.end(), src.begin());
			st[i].create();
		}
	}
	
	int query(int l, int r, int lo, int hi) {
		int cnt = 0;
		
		l += size(st) / 2;
		r += size(st) / 2;
		
		for(; l <= r; l /= 2, r /= 2) {
			if(l & 1) {
				cnt += st[l].order_of_key(hi + 1) - st[l].order_of_key(lo);
				++l;
			}
			
			if(~r & 1) {
				cnt += st[r].order_of_key(hi + 1) - st[r].order_of_key(lo);
				--r;
			}
		}
		
		return cnt;
	}
	
	void insert(int k, int x) {
		k += size(st) / 2;
		if(!st[k].empty()) return;
		st[k].insert(x);
		for(k /= 2; k; k /= 2) st[k].insert(x);
	}
	
	void remove(int k) {
		k += size(st) / 2;
		if(st[k].empty()) return;
		int x = st[k].P[0];
		st[k].erase(x);
		for(k /= 2; k; k /= 2) st[k].erase(x);
	}
};

const int INF = 1e9;

void solve() {

	int q;
	
	cin >> q;
	
	if(cin.eof()) exit(0);

	vector<dat> a(q);
	vector<ii> p(q);
	
	for(int i = 0; i < q; ++i) {
		int t, x, y, d;
		
		cin >> t >> x >> y;
				
		if(t == 3) cin >> d;
		
		p[i] = {x, y};
		a[i] = {t, x, y, d};
	}
	
	for(auto &[x, y] : p) {
		x += y;
		y = x - 2 * y;
	}
	
	sort(p.begin(), p.end());
	p.resize(unique(p.begin(), p.end()) - p.begin());
	
	SegTree st(p);
	
	for(int i = 0; i < q; ++i) {
		auto [t, x, y, d] = a[i];
		x += y;
		y = x - 2 * y;
		if(t == 1) {
			int k = lower_bound(p.begin(), p.end(), make_pair(x, y)) - p.begin();
			st.insert(k, y);
		} else if(t == 2) {
			int k = lower_bound(p.begin(), p.end(), make_pair(x, y)) - p.begin();
			st.remove(k);
		} else {
			int L = lower_bound(p.begin(), p.end(), make_pair(x - d, -INF)) - p.begin();
			int R = upper_bound(p.begin(), p.end(), make_pair(x + d, INF)) - p.begin() - 1;
			cout << st.query(L, R, y - d, y + d) << '\n';
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	while(1) solve();
	return 0;
}