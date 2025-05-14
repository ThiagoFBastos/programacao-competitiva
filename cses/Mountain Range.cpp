#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int INF = 1e9 + 1;
constexpr int N = 2e5 + 10;
 
int st[2 * N], n, ans;
 
void upd(int k, int x) {
 
	st[k += n] = x;
 
	for(k >>= 1; k; k >>= 1)
		st[k] = max(st[2 * k], st[2 * k + 1]);
}
 
int query(int l, int r) {
	int ans {};
 
	for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
		if(l & 1) ans = max(ans, st[l++]);
		if(~r & 1) ans = max(ans, st[r--]);
	}
 
	return ans;
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n;
 
	vector<int> lo(n), hi(n);
	vector<pair<int, int>> a(n), st;
 
	st.emplace_back(INF, -1);
 
	for(int i = 0; i < n; ++i) {
		cin >> a[i].first;
		a[i].second = i;
 
		while(st.back().first < a[i].first)
			st.pop_back();
 
		lo[i] = st.back().second;
 
		st.emplace_back(a[i].first, i);
	}
 
	st.clear();
	st.emplace_back(INF, n);
 
	for(int i = n - 1; i >= 0; --i) {
		while(st.back().first < a[i].first)
			st.pop_back();
 
		hi[i] = st.back().second;
 
		st.emplace_back(a[i].first, i);
	}
 
	sort(a.begin(), a.end());
 
	for(auto [v, k] : a) {
		int dp = 1 + max(query(lo[k] + 1, k - 1), query(k + 1, hi[k] - 1));
		ans = max(ans, dp);
		upd(k, dp);
	}
 
	cout << ans << '\n';
 
	return 0;
}
