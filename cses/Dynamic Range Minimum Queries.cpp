#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using vi = vector<int>;
 
class segtree {
 
	vi st;
	int n;
 
	void build(vi& data, int node, int low, int high) {
 
		if(low == high)
			st[node] = data[low];
 
		else {
 
			int L = (node << 1) + 1, R = (node << 1) + 2, mid = low + high >> 1;
 
			build(data, L, low, mid);
			build(data, R, mid + 1, high);
 
			st[node] = min(st[L], st[R]);
		}	
	}
 
	void update(int node, int k, int v, int low, int high) {
 
		if(low == high)
			st[node] = v;
 
		else {
 
			int mid = low + high >> 1, L = (node << 1) + 1, R = (node << 1) + 2;
 
			if(k <= mid)
				update(L, k, v, low, mid);
 
			else
				update(R, k, v, mid + 1, high);
 
			st[node] = min(st[L], st[R]);
		}
	}
 
	int query(int node, int l, int r, int low, int high) {
 
		if(l > r)
			return INT_MAX;
 
		else if(l == low && r == high)
			return st[node];
 
		int mid = low + high >> 1;
 
		return min(query((node << 1) + 1, l, min(r, mid), low, mid), query((node << 1) + 2, max(l, mid + 1), r, mid + 1, high));
	}
 
	public:
 
	segtree(vi& data) {
 
		n = data.size();
		st.resize((1 << static_cast<int>(ceil(log2(n))) + 1) - 1);
 
		build(data, 0, 0, n - 1);
	}
 
	int query(int l, int r) {
		return query(0, l, r, 0, n - 1);
	}
 
	void update(int k, int x) {
 
		update(0, k, x, 0, n - 1);
	}
};
 
int main() {
 
	int n, q;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
 
	cin >> n >> q;
 
	vi x(n);
 
	for(int k = 0; k < n; ++k)
		cin >> x[k];
 
	segtree st(x);
 
	while(q--) {
 
		int type, l, r;
 
		cin >> type >> l >> r;
 
		if(type == 1)
			st.update(l - 1, r);
 
		else
			cout << st.query(l - 1, r - 1) << '\n';		
	}
 
	return 0;
}
