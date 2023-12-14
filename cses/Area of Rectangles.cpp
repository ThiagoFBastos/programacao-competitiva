#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,mmx,sse2")
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
 
const int maxn = 2e6 + 1;
 
struct seg {
	int x, y1, y2, t;
};
 
bool operator<(seg s1, seg s2) {
	return s1.x < s2.x;
}
 
ii st[1 << 22];
int lazy[1 << 22];
 
void build(int = 0, int = maxn - 1, int = 1);
void push(int);
void upd(int, int, int, int = 0, int = maxn - 1, int = 1);
 
void build(int lo, int hi, int no) {
	lazy[no] = 0;
	st[no] = make_pair(0, hi - lo + 1);
	if(lo != hi) {
		int mid = (lo + hi) >> 1;
		build(lo, mid, no << 1);
		build(mid + 1, hi, (no << 1) | 1);
	}
}
 
void push(int no) {
	if(lazy[no]) {
		int left = no << 1, right = (no << 1) | 1;
		lazy[left] += lazy[no];
		lazy[right] += lazy[no];
		st[left].first += lazy[no];
		st[right].first += lazy[no];
		lazy[no] = 0; 
	}
}
 
void upd(int x, int l, int r, int lo, int hi, int no) {
	if(l > r) return;
	else if(r - l == hi - lo) {
		st[no].first += x;
		lazy[no] += x;
	} else {
		int mid = (lo + hi) >> 1, left = no << 1, right = (no << 1) | 1;
		push(no);
		upd(x, l, min(r, mid), lo, mid, left);
		upd(x, max(l, mid + 1), r, mid + 1, hi, right);
		if(st[left].first < st[right].first) st[no] = st[left];
		else if(st[left].first > st[right].first) st[no] = st[right];
		else st[no] = make_pair(st[left].first, st[left].second + st[right].second);
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, x = -1e6 - 1;
	ll area = 0;
	cin >> n;
	build();
	vector<seg> S(2 * n);
	for(int i = 0; i < n; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		y1 += 1'000'000;
		y2 += 1'000'000;
		S[i << 1] = {x1, y1, y2, 1};
		S[(i << 1) | 1] = {x2, y1, y2, -1};		
	}
	sort(S.begin(), S.end());
	for(int i = 0, k; i < 2 * n; i = k) {
		int cnt = maxn;
		if(st[1].first == 0) cnt -= st[1].second;
		area += cnt * (S[i].x - x + 0LL);
		for(k = i;k < 2 * n && S[i].x == S[k].x; ++k) upd(S[k].t, S[k].y1 + 1, S[k].y2);
		x = S[i].x;
	}
	cout << area << '\n';
	return 0;
}
