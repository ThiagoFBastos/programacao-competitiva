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

constexpr int N = 1e5 + 100;
constexpr int M = N * 20;

vector<int> adj[N], value;
int in[N], out[N], ordem[N], l[M], r[M], cnt[M], st[N], nodes;
int n, m, tms;

int init(int lo, int hi) {
	int no = nodes++;
	cnt[no] = 0;
	if(lo != hi) {
		int mid = (lo + hi) / 2;
		l[no] = init(lo, mid);
		r[no] = init(mid + 1, hi);
	}
	return no;
}

int upd(int k, int lo, int hi, int pai) {
	int no = nodes++;
	cnt[no] = 1 + cnt[pai];
	if(lo != hi) {
		int mid = (lo + hi) / 2;
		l[no] = l[pai], r[no] = r[pai];
		if(k <= mid) l[no] = upd(k, lo, mid, l[pai]);
		else r[no] = upd(k, mid + 1, hi, r[pai]);
	}
	return no;
}

int query(int k, int lo, int hi, int le, int ri) {
	if(lo == hi) return lo;
	int mid = (lo + hi) / 2;
	int ex = cnt[l[ri]] - cnt[l[le]];
	if(ex >= k) return query(k, lo, mid, l[le], l[ri]);
	return query(k - ex, mid + 1, hi, r[le], r[ri]);
}

void dfs(int u, int p) {
	in[u] = tms++;
	ordem[tms] = u;
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u);
	}
	out[u] = tms;
}
		
void solve() {
	nodes = tms = 0;
	
    cin >> n >> m;
	
    value.resize(n);
	
    for(int i = 0; i < n; ++i) {
		adj[i].clear();
		cin >> value[i];
	}
	
    auto p = value;
	
    sort(p.begin(), p.end());
	
    for(int& v : value)
        v = lower_bound(p.begin(), p.end(), v) - p.begin();
	
    for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(0, 0);
	
    st[0] = init(0, n - 1);
	
    for(int i = 1; i <= n; ++i)
        st[i] = upd(value[ordem[i]], 0, n - 1, st[i - 1]);
	
    for(int i = 0; i < m; ++i) {
		int x, k;
		
        cin >> x >> k;
		
        --x;
		
        cout << p[query(k, 0, n - 1, st[in[x]], st[out[x]])] << ' ';
	}

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