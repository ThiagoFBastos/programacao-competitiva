#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree <int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
using namespace std;
using namespace __gnu_pbds;
struct node {
	int value;
	node *left, *right;
	node(int v) : value {v}, left {}, right {} {}
};
const int MAXN = 1e5 + 1;
int pre_pos[MAXN], ino_pos[MAXN], n, pre[MAXN];
set<int> p;
void process(node** tree, int root, int L, int R) {
	int k = pre_pos[root];
	*tree = new node(root);
	p.erase(k);
	if(k < n - 1 && ino_pos[pre[k + 1]] < ino_pos[root]) 
		process(&(*tree)->left, pre[k + 1], L, ino_pos[root] - 1);
	if(!p.empty()) {
		int v = pre[*p.begin()];
		if(ino_pos[v] >= L && ino_pos[v] <= R)
			process(&(*tree)->right, v, ino_pos[root] + 1, R);
	}
}
vector<int> post_order;
void post(node * x) {
	if(!x) return;
	post(x->left);
	post(x->right);
	post_order.push_back(x->value);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	node *root {};
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> pre[i];
		pre_pos[pre[i]] = i;
		p.insert(i);
	}
	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		ino_pos[x] = i;
	}
	process(&root, pre[0], 0, n - 1);
	post(root);
	for(int v : post_order) cout << v << ' ';
	cout << '\n';
	return 0;
}
