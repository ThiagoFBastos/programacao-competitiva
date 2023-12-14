#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree <int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
using namespace std;
using namespace __gnu_pbds;
const int MAXN = 2e5 + 1;
int n, p[MAXN];
long long task_1() {
	ordered_set S;
	long long cnt = 0;
	for(int i = 1; i <= n; ++i) {
		cnt += (int)S.size() - S.order_of_key(p[i]);
		S.insert(p[i]);
	}
	return cnt;
}
int task_2() {
	int nxt[MAXN], cnt = 0;
	bool vis[MAXN];
	for(int i = 1; i <= n; ++i) {
		nxt[i] = p[i];
		vis[i] = false;
	}
	for(int k = 1; k <= n; ++k) {
		int size = 0, j = k;
		while(!vis[j]) {
			vis[j] = true;
			++size;
			j = nxt[j];
		}
		cnt += max(0, size - 1);
	}
	return cnt;
}
int task_3() {
	int s[MAXN], cnt = 0;
	for(int i = 0; i <= n; ++i) s[i] = INT_MAX;
	for(int k = 1; k <= n; ++k) {
		int j = lower_bound(s, s + n + 1, p[k]) - s;
		cnt = max(cnt, 1 + j);
		s[j] = p[k];
	}
	return n - cnt;
}
int task_4() {
	int x = 0, cnt = 0;
	vector<bool> move(n + 1, false);
	for(int i = 1; i <= n; ++i) {
		if(x > p[i]) {
			++cnt;
			move[i] = true;
		}
		x = max(x, p[i]);
	}
	x = 0;
	for(int i = n; i; --i) {
		if(x > p[i] && !move[i]) ++cnt;
		if(move[i]) x = max(x, p[i]);
	}
	return cnt;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) 
		cin >> p[i];
	cout << task_1() << ' ' << task_2() << ' ' << task_3() << ' ' << task_4() << '\n';
	return 0;
}
