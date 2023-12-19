#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
#define MAXN 200000
int v[MAXN], last_in[MAXN], p[MAXN], tour[2 * MAXN];
ll vs[MAXN];
vector<vi> T;
int k = 0, n;
class lazy_propagation {
	private:
	vector<ll> lazy;
	void update(int node, int l, int r, int x, int low, int high) {
		if(l > r) return;
		else if(l == low && r == high) {
			lazy[node] += x;
			if(l == r)
				vs[tour[l]] += x;
		}
		else { 
			int mid = (low + high) / 2;
			push(node, low, high);
			update((node << 1) + 1, l, min(r, mid), x, low, mid);
			update((node << 1) + 2, max(l, mid + 1), r, x, mid + 1, high);
		}
	}
	void push(int node, int low, int high) {
		if(lazy[node]) {
			int l = (node << 1) + 1, r = (node << 1) + 2;
			lazy[l] += lazy[node];
			lazy[r] += lazy[node];
			if(high - low == 1) {
				vs[tour[low]] += lazy[node];
				vs[tour[high]] += lazy[node];  
			}
			else if(high - low == 2)
				vs[tour[high]] += lazy[node];
			lazy[node] = 0;
		}
	}
	
	void reload(int node, int k, int low, int high) {
		if(low < high) {
			int mid = (low + high) / 2;
			push(node, low, high);
			if(k <= mid) reload((node << 1) + 1, k, low, mid);
			else reload((node << 1) + 2, k, mid + 1, high);
		}
	}
	public:
	lazy_propagation() {
		lazy.assign((1 << (static_cast<int>(log2(k)) + 2)) - 1, 0);
	}
	void reload(int v) {
		reload(0, p[v], 0, k - 1);
	}
	void update(int u, int x) {
		update(0, p[u], p[last_in[u]], x - v[u], 0, k - 1);
		v[u] = x;
	}
};
void dfs(int u) {
	last_in[u] = u;
	for(int w : T[u]) {
		if(last_in[w] == -1) {
			if(p[u] == -1) {
				p[u] = k;
				tour[k++] = u;
			}
 
			vs[w] += vs[u];
			dfs(w);
			last_in[u] = last_in[w];
		}
	}
	if(last_in[u] == u) {
		p[u] = k;
		tour[k++] = u;
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> n >> q;
	T.resize(n);
	for(int i = 0; i < n; ++i) {
		last_in[i] = p[i] = -1;
		cin >> v[i];
		vs[i] = v[i];
	}
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		T[u].push_back(v);
		T[v].push_back(u);
	}
 
	dfs(0); 
	lazy_propagation lp;
	while(q--) {
		int t, u;
		cin >> t >> u;
		--u;
		if(t == 1) {
			int x;
			cin >> x;
			lp.update(u, x);
		}
		else {
			lp.reload(u);
			cout << vs[u] << '\n';
		}
	}
    return 0;
}
