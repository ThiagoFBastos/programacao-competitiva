#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
class segtree {
 
	vector<ll> st;
	vector<pair<ll, ll>> lazy;
	int n;
 
	void build(vector<int>& t, int node, int low, int high) {
 
		lazy[node] = make_pair(0, 0);
 
		if(low == high)
			st[node] = t[low];
 
		else {
 
			int mid = (low + high) / 2;
 
			build(t, 2 * node + 1, low, mid);
			build(t, 2 * node + 2, mid + 1, high);
 
			st[node] = st[2 * node + 1] + st[2 * node + 2];
		}
	}
 
	void push(int node, int n) {
 
		if(lazy[node].first) {
 
			int left = 2 * node + 1, right = 2 * node + 2;
 
			lazy[left].first += lazy[node].first;
			lazy[left].second += lazy[node].second;
 
			int k = (n + 1) / 2;
			ll a1 = lazy[node].first, r = lazy[node].second;
 
			st[left] += k * (2LL * a1 + (k - 1LL) * r) / 2LL;
 
			a1 += r * k;			
			lazy[right].first += a1;
			lazy[right].second += r;
 
			k = n - k;
			st[right] += k * (2LL * a1 + (k - 1LL) * r) / 2LL;
 
			lazy[node] = make_pair(0, 0);
		}
	}
 
	ll query(int node, int l, int r, int low, int high) {
 
		if(l > r)
			return 0;
 
		else if(l == low && r == high)
			return st[node];
 
		int mid = (low + high) / 2;
 
		push(node, high - low + 1);
 
		return query(2 * node + 1, l, min(r, mid), low, mid) + query(2 * node + 2, max(l, mid + 1), r, mid + 1, high);
	}
 
	void update(int node, int l, int r, int low, int high) {
 
		if(high < l || low > r)
			return;
 
		else if(l <= low && r >= high) {
 
			int L = 1 + low - l, R = high - l + 1;
 
			lazy[node].first += L;
			++lazy[node].second;
 
			st[node] += (L + R) * (R - L + 1LL) / 2LL;
		}
 
		else {
 
			int mid = (low + high) / 2;
 
			push(node, high - low + 1);
 
			update(2 * node + 1, l, r, low, mid);
			update(2 * node + 2, l, r, mid + 1, high);
 
			st[node] = st[2 * node + 1] + st[2 * node + 2];
		}
	}
	
	public:
 
	segtree(vector<int>& t) {
 
		n = t.size();
 
		int N = (1 << ((int)log2(n) + 2)) - 1;
 
		st.resize(N);
		lazy.resize(N);
 
		build(t, 0, 0, n - 1);
	}
 
	ll query(int l, int r) {
 
		return query(0, l, r, 0, n - 1);
	}
 
	void update(int l, int r) {
 
		update(0, l, r, 0, n - 1);
	}
};
 
int main() {
 
	int n, q;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
 
	cin >> n >> q;
 
	vector<int> t(n);
 
	for(int k = 0; k < n; ++k)
		cin >> t[k];
 
	segtree st(t);
 
	while(q--) {
 
		int type, a, b;
 
		cin >> type >> a >> b;
 
		--a;
		--b;
 
		if(type == 1)
			st.update(a, b);
 
		else
			cout << st.query(a, b) << '\n';
	}
 
	return 0;
}
