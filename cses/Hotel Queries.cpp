#include <bits/stdc++.h>
 
using namespace std;
 
using vi = vector<int>;
 
class segtree {
 
	vi st;
	int n;
 
	void build(vi& data, int node, int low, int high) {
 
		if(low == high)
			st[node] = data[low];
 
		else {
 
			int L = (node << 1) + 1, R = (node << 1) + 2, mid = (low + high) >> 1;
 
			build(data, L, low, mid);
			build(data, R, mid + 1, high);
 
			st[node] = max(st[L], st[R]);
		}
	}
 
	int query(int node, int l, int r, int low, int high) {
 
		if(l > r)
			return 0;
 
		else if(l == low && r == high)
			return st[node];
 
		int mid = (low + high) >> 1;
 
		return max(query((node << 1) + 1, l, min(r, mid), low, mid), query((node << 1) + 2, max(l, mid + 1), r, mid + 1, high));
	}
 
	void update(int node, int k, int v, int low, int  high) {
 
		if(low == high)
			st[node] = v;
 
		else {
 
			int mid = (low + high) >> 1;
			int L = (node << 1) + 1, R = (node << 1) + 2;
 
			if(k <= mid) update(L, k, v, low, mid);
			else update(R, k, v, mid + 1, high);
 
			st[node] = max(st[L], st[R]);
		}
	}
 
	public:
 
	segtree(vi& x) {
 
		n = x.size();
		st.resize((1 << (int)log2(n) + 2) - 1);
 
		build(x, 0, 0, n - 1);
	}
 
	int query(int l, int r) {
 
		return query(0, l, r, 0, n - 1);
	}
 
	void update(int k, int v) {
 
		update(0, k, v, 0, n - 1);
	}
};
 
int main() {
 
	int n, m;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
 
	cin >> n >> m;
 
	vi x(n);
 
	for(int k = 0; k < n; ++k)
		cin >> x[k];
 
	segtree st(x);
 
	while(m--) {
 
		int s;
 
		cin >> s;
 
		int low = 0, high = n - 1, k = -1;
 
		while(low < high) {
 
			int mid = (low + high) >> 1;
 
			if(st.query(low, mid) >= s)
				high = mid;
 
			else
				low = mid + 1;
		}
 
		if(x[high] >= s) {
 
			cout << high + 1 << ' ';
			st.update(high, x[high] - s);
			x[high] -= s;
		}
 
		else
			cout << 0 << ' ';
	}
 
	cout << '\n';
 
	return 0;
}
