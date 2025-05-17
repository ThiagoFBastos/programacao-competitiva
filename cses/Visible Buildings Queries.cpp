#include <bits/stdc++.h>
 
using namespace std;
 
class segtree {
 
public:
	segtree(int n) : st(4 * n, 0), n(n) {}
 
	int query(int l, int r) {
		int ans {};
 
		for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
			if(l & 1) ans += st[l++];
			if(~r & 1) ans += st[r--];
		}
 
		return ans;
	}
 
	void upd(int k, int x) {
		st[k += n] += x;
		for(k >>= 1; k; k >>= 1)
			st[k] = st[k << 1] + st[(k << 1) | 1];
	}
 
private:
	vector<int> st;
	int n;
};
 
vector<int> firstTaller(vector<int>& h) {
	constexpr int INF = 1e9 + 1;
	int n = h.size();
	vector<pair<int, int>> st(1, {INF, 0});
	vector<int> lo(n);
 
	for(int i = 0; i < n; ++i) {
		while(st.back().first < h[i])
			st.pop_back();
 
		lo[i] = st.back().second;
 
		st.emplace_back(h[i], i + 1);
	}
 
	return lo;
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n, q;
 
	cin >> n >> q;
 
	vector<int> height(n), answer(q);
	vector<vector<int>> incremment(n + 1);
	vector<vector<pair<int, int>>> queries(n + 1);
	segtree st(n);
 
	for(int& h : height) cin >> h;
 
	for(int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		queries[l].emplace_back(r, i);
	}
 
	auto taller = firstTaller(height);
 
	for(int i = 0; i < n; ++i)
		incremment[taller[i]].push_back(i);
 
	for(int pos : incremment[0])
		st.upd(pos, 1);
 
	for(int l = 1; l <= n; ++l) {
		for(auto [r, id] : queries[l])
			answer[id] = st.query(l - 1, r - 1);
 
		for(int pos : incremment[l])
			st.upd(pos, 1);
	}
 
	for(int ans : answer) cout << ans << '\n';
 
	return 0;
}