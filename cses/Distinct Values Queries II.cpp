#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int INF = 1e9;
 
class SegTree {
 
public:
 
	SegTree(int n): data(2 * n, INF), n (n) {}
 
	void update(int k, int x) {
		data[k += n] = x;
 
		for(k >>= 1; k; k >>= 1)
			data[k] = min(data[k << 1], data[(k << 1) | 1]);
	}
 
	int query(int l, int r) {
		int ans {INF};
 
		for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
			if(l & 1) ans = min(ans, data[l++]);
			if(~r & 1) ans = min(ans, data[r--]);
		}
 
		return ans;
	}
 
private:
	vector<int> data;
	int n;
};
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, q;
	set<pair<int, int>> st;
 
	cin >> n >> q;
 
	vector<int> a(n);
	SegTree seg(n);
 
	auto update = [&](int k, int x) {
		if(a[k] == x)
			return;
 
		auto it = st.find(make_pair(a[k], k));
		
		if(it != st.begin() && prev(it)->first == a[k]) {
			auto before = prev(it);
			auto [_, i] = *before;
 
			auto after = st.upper_bound(make_pair(a[k], k));
 
			if(after != st.end() && after->first == a[k])
				seg.update(i, after->second);
			else
				seg.update(i, INF);
		}
 
		st.erase(it);
 
		it = st.upper_bound(make_pair(x, k));
 
		if(it != st.end() && it->first == x)
			seg.update(k, it->second);
		else
			seg.update(k, INF);
		
		if(it != st.begin() && prev(it)->first == x) {
			auto before = prev(it);
			auto [_, i] = *before;
			seg.update(i, k);
		}
 
		st.emplace(x, k);
		a[k] = x;
	};
 
	auto query = [&seg](int l, int r) {
		return seg.query(l, r) > r;
	};
 
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		st.emplace(a[i], i);
	}
 
	for(int i = 0; i < n; ++i) {
		auto it = st.find(make_pair(a[i], i));
		auto after = next(it);
 
		if(after != st.end() && after->first == a[i])
			seg.update(i, after->second);
	}
 
	while(q--) {
		int type, a1, a2;
 
		cin >> type >> a1 >> a2;
 
		if(type == 1)
			update(a1 - 1, a2);
		else
			cout << (query(a1 - 1, a2 - 1) ? "YES\n" : "NO\n");
	}
 
	return 0;
}
