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

int n;
vector<vector<int>> g;
vector<int> a;

template<class T>
struct SegTree {
	vector<T> st;
	int n;
	
	SegTree() {n = 0;}
	
	SegTree(int n) : n {n} {
		st.assign(2 * n + 1, 0);
	}
	
	void upd(int k, T x) {
		k += n;
		st[k] = x;
		for(k /= 2; k > 0; k /= 2) st[k] = max(st[2 * k], st[2 * k + 1]);
	}
	
	T query(int l, int r) {
		T ans {};
		for(l += n, r += n; l <= r; l /= 2, r /= 2) {
			if(l & 1) ans = max(st[l++], ans);
			if(~r & 1) ans = max(st[r--], ans);
		}
		return ans;
	}
};

SegTree<int> st;
vector<int> lis;

void dfs(int u, int p = -1) {
	int prev = st.query(a[u], a[u]);
	lis[u] = 1 + st.query(0, a[u] - 1);
	st.upd(a[u], lis[u]);
	if(p != -1) lis[u] = max(lis[u], lis[p]);
	for(int v : g[u]) {
		if(v == p) continue;
		dfs(v, u);
	}
	st.upd(a[u], prev);
}

void solve() {
	cin >> n;
	
	g.resize(n);
	a.resize(n);
	lis.assign(n, 0);
	
	st = SegTree<int>(n);
	
	for(int& x : a) cin >> x;
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	auto p = a;
	sort(p.begin(), p.end());
	for(int& x : a) x = lower_bound(p.begin(), p.end(), x) - p.begin();
	
	dfs(0); 
	
	for(int x : lis) cout << x << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
   	
    int t = 1;
  	//cin >> t;
    while(t--) solve();
    return 0;
}
