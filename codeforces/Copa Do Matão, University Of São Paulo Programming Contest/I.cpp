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

struct Node {
	i64 sum;
	Node* left, *right;
};

struct SegTree {
	vector<Node*> st;
	
	Node* init(int lo, int hi) {
		Node *no = new Node;
		no->sum = 0;
		if(lo != hi) {
			int mid = (lo + hi) / 2;
			no->left = init(lo, mid);
			no->right = init(mid + 1, hi);
		}
		return no;
	}
	
	Node* upd(int x, int y, int lo, int hi, Node *root) {
		Node *no = new Node;
		if(lo == hi) no->sum = root->sum + y;
		else {
			int mid = (lo + hi) / 2;
			if(x <= mid) {
				no->left = upd(x, y, lo, mid, root->left);
				no->right = root->right;
			} else {
				no->left = root->left;
				no->right = upd(x, y, mid + 1, hi, root->right);
			}
			no->sum = no->left->sum + no->right->sum;
		}
		return no;
	}

	i64 query_sum(i64 d, int lo, int hi, Node* left, Node *right) {
		i64 s = right->sum - left->sum;

		if(d <= 0) return 0;
		else if(lo == hi) return s <= d ? s : 0;

		int mid = (lo + hi) / 2;

		
		if(s <= d) return right->sum - left->sum;
		

		i64 sum = right->left->sum - left->left->sum;
	
		i64 L = query_sum(d, lo, mid, left->left, right->left);
		i64 R = query_sum(d - sum, mid + 1, hi, left->right, right->right);

		return L + R;
	}
		
	SegTree(vector<ii>& a) {
		int n = size(a);
		st.resize(n + 1);
		st[0] = init(0, n - 1);
		for(int i = 1; i <= n; ++i) st[i] = upd(a[i - 1].second, a[i - 1].first, 0, n - 1, st[i - 1]);
	}
};

void solve() {
	int n, q;
	i64 ans = 0;

	cin >> n >> q;

	vector<ii> a(n);
	vector<int> p;

	for(auto& [x, y] : a) {
		cin >> x;
		p.push_back(x);
	}
		
	sort(p.begin(), p.end());

	for(auto& [x, y] : a) y = lower_bound(p.begin(), p.end(), x) - p.begin();
		
	SegTree st(a);

	while(q--) {
		int x, y;
		i64 z;

		cin >> x >> y >> z;
		
		int l = ((x + ans - 1) % n + n) % n, r = ((y + ans - 1) % n + n) % n;
		i64 d = z + ans;
		
		i64 v = st.query_sum(d, 0, n - 1, st.st[l], st.st[r + 1]);

		cout << v << '\n';

		ans = v;
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


