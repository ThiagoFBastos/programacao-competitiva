#include <bits/stdc++.h>
 
using namespace std;
 
using vi = vector<int>;
 
class segtree {
 
	vi st;
	int n;
 
	void build(int node, int low, int high) {
 
		if(low == high)
			st[node] = 1;
 
		else {
 
			int mid = (low + high) / 2;
 
			build(2 * node + 1, low, mid);
			build(2 * node + 2, mid + 1, high);
 
			st[node] = st[2 * node + 1] + st[2 * node + 2];
		}
	}
 
	void update(int node, int k, int low, int high) {
 
		if(low == high)
			st[node] = 0;
 
		else {
 
			int mid = (low + high) / 2;
 
			if(k <= mid) update(2 * node + 1, k, low, mid);
			else update(2 * node + 2, k, mid + 1, high);
 
			st[node] = st[2 * node + 1] + st[2 * node + 2];
		}
	}
 
	int query(int node, int k, int low, int high) {
 
		if(low == high)
			return high;
 
		int mid = (low + high) / 2;
 
		if(k <= st[2 * node + 1])
			return query(2 * node + 1, k, low, mid);
 
		return query(2 * node + 2, k - st[2 * node + 1], mid + 1, high);
	}
 
	public:
 
	segtree(int n) {
 
		this->n = n;
		st.resize((1 << (int)log2(n) + 2) - 1);
		build(0, 0, n - 1);
	}
 
	int query(int k) {
 
		return query(0, k, 0, n - 1);
	}
 
	void clear(int k) {
 
		update(0, k, 0, n - 1);
	}
};
 
int main() {
 
	int n;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
 
	cin >> n;
 
	vi a(n);
	segtree st(n);
 
	for(int k = 0; k < n; ++k)
		cin >> a[k];
 
	for(int k = 0; k < n; ++k) {
 
		int p, j;
 
		cin >> p;
 
		j = st.query(p);
 
		cout << a[j] << ' ';
 
		st.clear(j);
	}
 
	cout << '\n';
 
	return 0;
}
