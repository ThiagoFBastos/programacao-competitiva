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

const int inf = 1e9;

template<class T>
struct SegTree {
	vector<T> st;
	int n;
	
	SegTree() {}
	
	SegTree(vector<T> a) {
		n = a.size();
		st.resize(2 * n + 1);
		for(int k = n; k < 2 * n; ++k) st[k] = a[k - n];
		for(int k = n - 1; k > 0; --k) st[k] = max(st[2 * k], st[2 * k + 1]);
	}
	
	void upd(int k, T x) {
		k += n;
		st[k] = x;
		for(k /= 2; k > 0; k /= 2) st[k] = st[k] = max(st[2 * k], st[2 * k + 1]);
	}
	
	T query(int l, int r) {
		T ans = -inf;
		for(l += n, r += n; l <= r; l /= 2, r /= 2) {
			if(l & 1) ans = max(ans, st[l++]);
			if(~r & 1) ans = max(ans, st[r--]);
		}
		return ans;
	}
};

int n, tms;
vector<vector<int>> g;
vector<int> f, minPos, maxPos, L, R;

void dfs(int u, int p) {
	L[u] = R[u] = tms++;	
	minPos[f[u]] = min(minPos[f[u]], tms - 1);
	maxPos[f[u]] = max(maxPos[f[u]], tms - 1);

	for(int v : g[u]) {
		if(v == p) continue;
		dfs(v, u);
		R[u] = max(R[u], R[v]);
	}
}

int cnt;
SegTree<int> maxSt, minSt;

void count(int u, int p) {
	for(int v : g[u]) {
		if(v == p) continue;
		if(-minSt.query(L[v], R[v]) >= L[v] && maxSt.query(L[v], R[v]) <= R[v]) ++cnt;
		count(v, u);
	}
}
 
void solve() {

	cin >> n;
	
	g.clear();
	g.resize(n);
	f.resize(n);
	minPos.assign(n + 1, inf);
	maxPos.assign(n + 1, -inf);
	L.resize(n);
	R.resize(n);
	tms = cnt = 0;
	
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	for(int& v : f) cin >> v;

	dfs(0, 0);

	for(int& x : minPos) x *= -1;
	
	vector<int> a(n), b(n);
	
	for(int i = 0; i < n; ++i) {
		a[L[i]] = minPos[f[i]];
		b[L[i]] = maxPos[f[i]];
	}
	
	minSt = SegTree<int>(a);
	maxSt = SegTree<int>(b);
	
	count(0, 0);
	
	cout << cnt << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
 	return 0;
}
