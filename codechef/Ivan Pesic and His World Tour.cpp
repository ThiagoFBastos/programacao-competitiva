#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 250010, MOD = 1e9 + 9;

i64 exp(i64 n, int p, int m) {
	i64 ans = 1;
	n %= m;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % m;
		n = n * n % m;
	}
	return ans;
}

template<int m>
struct modInt {
	int val;
	
	modInt() {val = 0;}
	modInt(int val) : val {val} {}
	
	modInt operator^(i64 p) {
		return {int(exp(val, p, m))};
	}
	
	modInt& operator^=(int p) {
		val = exp(val, p, m);
		return *this;
	}

	modInt operator+(modInt x) {
		int ans = val + x.val;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(modInt x) {
		int ans = val - x.val;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(modInt x) {
		val += x.val;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(modInt x) {
		val -= x.val;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(modInt x) {
		return {int(((i64)val * x.val % m + m) % m)};
	}

	modInt& operator*=(modInt x) {
		val = ((i64)val * x.val % m + m) % m;
		return *this;
	}
	
	modInt operator/(modInt x) {
		return {int((val * exp(x.val, m - 2, m) % m + m) % m)};
	}
	
	modInt& operator/=(modInt x) {
		val = (val * exp(x.val, m - 2, m) % m + m) % m;
		return *this;
	}
	
	modInt operator+(i64 x) {
		x = (x % m + m) % m;
		int ans = val + x;
		if(ans >= m) ans -= m;
		return {ans};
	}
	
	modInt operator-(i64 x) {
		x = (x % m + m) % m;
		int ans = val - x;
		if(ans < 0) ans += m;
		return {ans};
	}
	
	modInt& operator+=(i64 x) {
		x = (x % m + m) % m;
		val += x;
		if(val >= m) val -= m;
		return *this;
	}
	
	modInt& operator-=(i64 x) {
		x = (x % m + m) % m;
		val -= x;
		if(val < 0) val += m;
		return *this;
	}
	
	modInt operator*(i64 x) {
		x = (x % m + m) % m;
		return {int((i64)val * x % m)};
	}
	
	modInt& operator*=(i64 x) {
		x = (x % m + m) % m;
		val = (i64)val * x % m;
		return *this;
	}
	
	modInt operator/(i64 x) {
		return {int(val * exp(x, m - 2, m) % m)};
	}
	
	modInt& operator/=(i64 x) {
		val = val * exp(x, m - 2, m) % m;
		return *this;
	}

	bool operator==(modInt other) {
		return val == other.val;
	}

	bool operator!=(modInt other) {
		return val != other.val;
	}
};

template<int m>
ostream& operator<<(ostream& os, modInt<m> v) {
	os << v.val;
	return os;
}

template<int m>
istream& operator>>(istream& is, modInt<m>& v) {
	is >> v.val;
	return is;
}

using imod = modInt<MOD>;

vector<int> adj[N];
int head[N];
int in[N], out[N], sz[N], depth[N], par[N];
int n, q;
imod st[4 * N], pt[N], pps[N], a[N], temp[N];

struct hld {
	int tms;

	void build(imod a[]) {
		for(int i = 0; i < n; ++i) st[i + n] = a[i];
		for(int i = n - 1; i; --i) st[i] = st[i << 1] + st[(i<<1)|1];
	}

	imod query(int l, int r) {
		imod ans;
		for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
			if(l & 1) ans += st[l++];
			if(~r & 1) ans += st[r--];
		}
		return ans;
	}

	void upd(int k, imod x) {
		st[k += n] = x;
		for(k >>= 1; k; k >>= 1) st[k] = st[k<<1] + st[(k<<1)|1];
	}

	imod queryPath(int a, int b) {
		imod ans;
		while(head[a] != head[b]) {
			if(depth[head[a]] > depth[head[b]]) swap(a, b);
			ans += query(in[head[b]], in[b]);
			b = par[head[b]];
		}
		if(depth[a] > depth[b]) swap(a, b);
		return ans + query(in[a], in[b]);
	}

	void updNode(int v, imod x) {
		upd(in[v], x);
	}
	
	int lca(int a, int b) {
		while(head[a] != head[b]) {
			if(depth[head[a]] > depth[head[b]]) swap(a, b);
			b = par[head[b]];
		}
		if(depth[a] > depth[b]) swap(a, b);
		return a;
	}

	int dist(int a, int b) {
		return depth[a]+depth[b]-2*depth[lca(a,b)];
	}

	void dfssize(int u, int p) {
		int t = 1;
		par[u] = p;
		for(int& v : adj[u]) {
			if(v == p) continue;
			depth[v] = 1 + depth[u];
			dfssize(v, u);
			t += sz[v];
			if(sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
		}
		sz[u] = t;
	}

	void dfshld(int u, int p) {
		in[u] = tms++;
		for(int v : adj[u]) {
			if(v == p) continue;	
			else if(2 * sz[v] >= sz[u]) head[v] = head[u];
			dfshld(v, u);
		}
		out[u] = tms - 1;
	}
		
	hld() {
		for(int i = 0; i < n; ++i) {
			temp[i] = a[i];
			head[i] = i;
			sz[i] = 0;
		}
		dfssize(0, 0);
		tms = 0;
		dfshld(0, 0);
		for(int i = 0; i < n; ++i) a[in[i]] = temp[i];
		build(a);
	}
};


void solve() {
	cin >> n >> q;
	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		a[i] = pt[v];
		adj[i].clear();
	}		
	for(int i = 1; i < n; ++i) {
		int x,y;
		cin>>x>>y;
		--x,--y;
		adj[x].pb(y); adj[y].pb(x);
	}
	hld S;
	while(q--) {
		int type, a0, a1;
		cin >> type >> a0 >> a1;
		if(type == 1) {
			--a0, --a1;
			int L = S.dist(a0,a1)+1;
			cout<<(S.queryPath(a0,a1)==pps[L]?"Yes\n":"No\n");
		} else S.updNode(a0 - 1, pt[a1]);
	}
}

int main() {
	pt[0] = 1;
	for(int i = 1; i < N; ++i) {
		pt[i] = pt[i - 1] * 128571092;
		pps[i] = pps[i - 1] + pt[i];
	}
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}