#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using vll = vector<ll>;
 
class segtree {
 
	vll lazy, data;
	int n;
 
	void update(int node, int u, int L, int R, int low, int high) {
 
		if(L > R) return;
 
		else if(L == low && R == high) {
 
			lazy[node] += u;
 
			if(low == high)
				data[low] += u;
		}
 
		else {
 
			int mid = low + high >> 1;
 
			push(node, low, high);
 
			update((node << 1) + 1, u, L, min(R, mid), low, mid);
			update((node << 1) + 2, u, max(L, mid + 1), R, mid + 1, high);
		}
	}
 
	void push(int node, int L, int R) {
 
		if(lazy[node]) {
 
			lazy[(node << 1) + 1] += lazy[node];
			lazy[(node << 1) + 2] += lazy[node];
 
			if(R - L == 1) {
 
				data[L] += lazy[node];
				data[R] += lazy[node];
			}
 
			else if(R - L == 2)
				data[R] += lazy[node];
 
			lazy[node] = 0;
		}
	}
 
	ll query(int node, int k, int low, int high) {
 
		if(low == high)
			return data[k];
 
		int mid = low + high >> 1;
 
		push(node, low, high);
 
		if(k <= mid) return query((node << 1) + 1, k, low, mid);
 
		return query((node << 1) + 2, k, mid + 1, high);
	}
 
	public:
	
	segtree(vll& data) {
 
		this->data = data;
		n = data.size();
		lazy.assign((1 << (int)log2(n) + 2) - 1, 0);
	}
 
	void update(int l, int r, int u) {
 
		update(0, u, l, r, 0, n - 1);
	}
 
	ll query(int k) {
 
		return query(0, k, 0, n - 1);
	}	
};
 
int main() {
 
	int n, q;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
 
	cin >> n >> q;
 
	vll x(n);
 
	for(int k = 0; k < n; ++k)
		cin >> x[k];
 
	segtree st(x);
 
	while(q--) {
 
		int type, l, r, u;
 
		cin >> type >> l;
 
		--l;
 
		if(type == 1) {
 
			cin >> r >> u;
 
			st.update(l, r - 1, u);
		}
 
		else
			cout << st.query(l) << '\n';
	}
 
	return 0;
}
