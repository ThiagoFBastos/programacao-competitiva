#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
 
template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
 
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;
 
const int maxn = 2e5;
struct Node {
	Node *L, *R;
	ll V;
	Node() {}
	Node(ll v, Node* l = nullptr, Node*r = nullptr) : V{v}, L{l}, R{r} {}
};
int a[maxn], m = 1, n, q;
Node *roots[maxn];
Node *build(int l, int r) {
	if(l == r)
		return new Node(a[l]);
	int mid = (l + r) / 2;
	Node *L, *R;
	L = build(l, mid);
	R = build(mid + 1, r);
	return new Node(L->V + R->V, L, R);
}
Node *update(Node *no, int k, int x, int l, int r) {
	if(l == r) return new Node(x);
	int mid = (l + r) / 2;
	Node *L, *R;
	if(k <= mid) {
		R = no->R;
		L = update(no->L, k, x, l, mid);
	}
	else {
		L = no->L;
		R = update(no->R, k, x, mid + 1, r);
	}
	return new Node(L->V + R->V, L, R);
}
ll query(Node *no, int L, int R, int l, int r) {
	if(L > R) return 0;
	else if(R - L == r - l) return no->V;
	int mid = (l + r) / 2;
	return query(no->L, L, min(R, mid), l, mid) + query(no->R, max(L, mid + 1), R, mid + 1, r);
}
ll query(int k, int l, int r) {
	return query(roots[k], l, r, 0, n - 1);
}
void update(int k, int j, int x) {
	roots[k] = update(roots[k], j, x, 0, n - 1);
}
void copy(int k) {
	roots[m++] = roots[k];
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for(int i = 0; i < n; ++i) cin >> a[i];
	roots[0] = build(0, n - 1);
	while(q--) {
		int t, a, b, c;
		cin >> t >> a;
		if(t == 1) {
			cin >> b >> c;
			--a, --b;
			update(a, b, c);
		}
		else if(t == 2) {
			cin >> b >> c;
			cout << query(a - 1, b - 1, c- 1) << '\n';			
		}
		else 
			copy(a - 1);
	}
	return 0;
}
