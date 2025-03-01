#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7;

int n, tms;

vector<vector<int>> g;
vector<int> L, R;

void dfs(int u, int p) {
	L[u] = R[u] = tms++;
	for(int v : g[u]) {
		if(v == p) continue;
		dfs(v, u);
		R[u] = R[v];
	}
}

int mod_sum(int x) {
	return x >= mod ? x - mod : x;
}

struct SegTree {
	vector<int> dp, lazy, cnt;
	int n;
	
	void create(int lo, int hi, int no = 1) {
		dp[no] = lazy[no] = 0;
		cnt[no] = hi - lo + 1;
		if(lo != hi) {
			int mid = (lo + hi) / 2;
			create(lo, mid, 2 * no);
			create(mid + 1, hi, 2 * no + 1);
		}
	}
	
	SegTree(int n) : n {n} {
		int K = 1 << (33 - __builtin_clz(n));
		dp.resize(K);
		lazy.resize(K);
		cnt.resize(K);
		create(0, n - 1);	
	}
	
	void push(int no) {
		if(!lazy[no]) return;
		int left = 2 * no, right = 2 * no + 1;
		dp[left] = mod_sum(dp[left] + 1LL * cnt[left] * lazy[no] % mod);
		dp[right] = mod_sum(dp[right] + 1LL * cnt[right] * lazy[no] % mod);
		lazy[left] = mod_sum(lazy[left] + lazy[no]);
		lazy[right] = mod_sum(lazy[right] + lazy[no]);
		lazy[no] = 0;
	}
	
	void upd(int l, int r, int x, int lo, int hi, int no = 1) {
		if(l > r) return;
		else if(r - l == hi - lo) {
			dp[no] = mod_sum(dp[no] + 1LL * cnt[no] * x % mod);
			lazy[no] = mod_sum(lazy[no] + x);
		} else {
			int mid = (lo + hi) / 2;
			push(no);
			upd(l, min(r, mid), x, lo, mid, 2 * no);
			upd(max(l, mid + 1), r, x, mid + 1, hi, 2 * no + 1);
			dp[no] = mod_sum(dp[2 * no] + dp[2 * no + 1]);
		}
	}
	
	int query(int l, int r, int lo, int hi, int no = 1) {
		if(l > r) return 0;
		else if(r - l == hi - lo) return dp[no];	
		int mid = (lo + hi) / 2;
		push(no);
		int L = query(l, min(r, mid), lo, mid, 2 * no);
		int R = query(max(l, mid + 1), r, mid + 1, hi, 2 * no + 1);
		return mod_sum(L + R);
	}
	
	void rem(int k, int lo, int hi, int no = 1) {
		--cnt[no];
		if(lo != hi) {
			int mid = (lo + hi) / 2;
			k <= mid ? rem(k, lo, mid, 2 * no) : rem(k, mid + 1, hi, 2 * no + 1);
		}
	}
	
	void upd(int l, int r, int x) {
		upd(l, r, x, 0, n - 1);
	}
	
	int query(int l, int r) {
		return query(l, r, 0, n - 1);
	}
	
	void rem(int k) {
		return rem(k, 0, n - 1);
	}
};

using ii = pair<int, int>;

void solve() {
	cin >> n;
	
	g.clear();
	L.resize(n);
	R.resize(n);
	g.resize(n);
	tms = 0;
	
	for(int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		g[--p].push_back(i);
	}
	
	vector<ii> rat(n);
	
	for(int i = 0; i < n; ++i) {
		int r;
		cin >> r;
		rat[i] = {r, i};
	}
	
	dfs(0, 0);
	
	sort(rat.begin(), rat.end());
	
	SegTree par(n), child(n);

	int ans = 0;
	
	for(auto [x, k] : rat) {
		int dp = mod_sum(par.query(L[k], L[k]) + child.query(L[k], R[k]));
		par.upd(L[k] + 1, R[k], mod_sum(1 + dp));
		child.upd(L[k], L[k], mod_sum(1 + dp));
		ans = mod_sum(ans + dp);
	}
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}