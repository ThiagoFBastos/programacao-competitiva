#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
 
class segtree {
 
	vi set_lazy;
	vector<ll> st, sum_lazy;
	int n;
 
	void Build(vi& x, int node, int low, int high) {
 
		set_lazy[node] = 0;
		sum_lazy[node] = 0;
 
		if(low == high)
			st[node] = x[low];
 
		else {
 
			int mid = (low + high) / 2;
 
			Build(x, 2 * node + 1, low, mid);
			Build(x, 2 * node + 2, mid + 1, high);
 
			st[node] = st[2 * node + 1] + st[2 * node + 2];
		}
	}
 
	void push(int node, int n) {
 
		int L = 2 * node + 1, R = 2 * node + 2;
 
		if(set_lazy[node]) {
 
			set_lazy[L] = set_lazy[R] = set_lazy[node];
			sum_lazy[L] = sum_lazy[R] = 0;
 
			st[L] = (n + 1LL) / 2LL * set_lazy[node];
			st[R] = (n - (n + 1LL) / 2LL) * set_lazy[node];
 
			set_lazy[node] = 0;
		}
 
		else if(sum_lazy[node]) {
 
			if(set_lazy[L])
				set_lazy[L] += sum_lazy[node];
	
			else
				sum_lazy[L] += sum_lazy[node];
			
			if(set_lazy[R])
				set_lazy[R] += sum_lazy[node];
	
			else
				sum_lazy[R] += sum_lazy[node];
 
			st[L] += (n + 1LL) / 2LL * sum_lazy[node];
			st[R] += (n - (n + 1LL) / 2LL) * sum_lazy[node];
 
			sum_lazy[node] = 0;
		}
	}
 
	void Set(int node, int x, int l, int r, int low, int high) {
 
		if(l > r)
			return;
 
		else if(l == low && r == high) {
 
			sum_lazy[node] = 0;
			set_lazy[node] = x;
			st[node] = x * (high - low + 1LL);
		}
 
		else {
 
			int mid = (low + high) / 2;
 
			push(node, high - low + 1);
 
			Set(2 * node + 1, x, l, min(r, mid), low, mid);
			Set(2 * node + 2, x, max(l, mid + 1), r, mid + 1, high);
 
			st[node] = st[2 * node + 1] + st[2 * node + 2];
		}
	}
 
	void Sum(int node, int x, int l, int r, int low, int high) {
 
		if(l > r)
			return;
 
		else if(l == low && r == high) {
 
			if(set_lazy[node])
				set_lazy[node] += x;
 
			else
				sum_lazy[node] += x;
 
			st[node] += x * (high - low + 1LL);
		}
 
		else {
 
			int mid = (low + high) / 2;
 
			push(node, high - low + 1);
 
			Sum(2 * node + 1, x, l, min(r, mid), low, mid);
			Sum(2 * node + 2, x, max(l, mid + 1), r, mid + 1, high);
 
			st[node] = st[2 * node + 1] + st[2 * node + 2];
		}
	}
 
	ll query(int node, int l, int r, int low, int high) {
 
		if(l > r)
			return 0;
 
		else if(l == low && r == high)
			return st[node];
 
		push(node, high - low + 1);
 
		int mid = (low + high) / 2;
 
		return query(2 * node + 1, l, min(r, mid), low, mid) + query(2 * node + 2, max(l, mid + 1), r, mid + 1, high);		
	}
 
	public:
 
	segtree(vi &x) {
 
		n = x.size();
 
		int N = (1 << ((int)log2(n) + 2)) - 1;
 
		st.resize(N);
		set_lazy.resize(N);
		sum_lazy.resize(N);
 
		Build(x, 0, 0, n - 1); 
	} 
 
	ll query(int l, int r) {
		return query(0, l, r, 0, n - 1);
	}
 
	void Set(int l, int r, int x) {
		Set(0, x, l, r, 0, n - 1);
	}
 
	void Sum(int l, int r, int x) {
		Sum(0, x, l, r, 0, n - 1);
	}
};
 
int main() {
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
 
	int n, q;
 
	cin >> n >> q;
 
	vi x(n);
 
	for(int k = 0; k < n; ++k)
		cin >> x[k];
 
	segtree st(x);
 
	while(q--) {
 
		int t, a, b;
 
		cin >> t >> a >> b;
 
		--a, --b;
 
		if(t == 3)	cout << st.query(a, b) << '\n';
		else if(t == 2) {int y; cin >> y; st.Set(a, b, y); }
		else {int y; cin >> y; st.Sum(a, b, y); } 
	}
	
	return 0;
}
