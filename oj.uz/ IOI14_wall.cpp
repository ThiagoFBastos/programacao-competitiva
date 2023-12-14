#include "wall.h"
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;	
 
const int N = 1 << 22;
 
struct Item {
	int type;
	int x, y;
};
 
Item lazy[N];
bool marked[N];
 
int F(Item i, int x) {
	if(i.type == 0) return max(i.x, min(i.y, x));
	return min(i.x, max(i.y, x));
}
 
Item A[2][2][4][4][4][4];
 
Item merge(Item a, Item b) {
	int p[4] = {a.x, a.y, b.x, b.y};
 
	sort(p, p + 4);
 
	auto [_, ax, ay] = a;
	auto [__, bx, by] = b;
 
	ax = lower_bound(p, p + 4, ax) - p;
	ay = lower_bound(p, p + 4, ay) - p;
	bx = lower_bound(p, p + 4, bx) - p;
	by = lower_bound(p, p + 4, by) - p;
 
	auto k = A[a.type][b.type][ax][ay][bx][by];
 
	return {k.type, p[k.x], p[k.y]};
}
 
void build(int l, int r, int k = 1) {
	lazy[k] = {0, 0, INF};
	if(l != r) {
		build(l, (l + r) / 2, 2 * k);
		build((l + r) / 2 + 1, r, 2 * k + 1);
	}
}
 
void push(int k) {
	if(!marked[k]) return;
	for(int i : {2 * k, 2 * k + 1}) {
		marked[i] = true;
		lazy[i] = merge(lazy[k], lazy[i]);
	}
	lazy[k] = {0, 0, INF};
	marked[k] = false;
}
 
void upd(int l, int r, Item x, int lo, int hi, int k = 1) {
	if(l > r || lo > hi || r < lo || hi < l) return;
	else if(lo >= l && hi <= r) {
		lazy[k] = merge(x, lazy[k]);
		marked[k] = true;
	} else {
		int m = (lo + hi) / 2;
		push(k);
		upd(l, r, x, lo, m, 2 * k);
		upd(l, r, x, m + 1, hi, 2 * k + 1);
	}
}
 
int query(int i, int lo, int hi, int k = 1) {
	if(lo == hi) return F(lazy[k], 0);
	int m = (lo + hi) / 2;
	push(k);
	return i <= m ? query(i, lo, m, 2 * k) : query(i, m + 1, hi, 2 * k + 1);
}
 
void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	
	build(0, n - 1);
 
	for(int at : {0,1})
	for(int bt : {0,1})
	for(int ax : {0,1,2,3})
	for(int ay : {0,1,2,3})
	for(int bx : {0,1,2,3})
	for(int by : {0,1,2,3})
	for(int t : {0, 1})
	for(int i : {0,1,2,3})
	for(int j : {0,1,2,3}) {
		bool ok = true;
		for(int x : {0,1,2,3}) ok = ok && F({at, ax, ay}, F({bt, bx, by}, x)) == F({t, i, j}, x);
		if(ok) A[at][bt][ax][ay][bx][by] = {t, i, j};
	}
 
	for(int i = 0; i < k; ++i) {
		Item v;
 
		if(op[i] == 1) {
			v.type = 0;
			v.x = height[i];
			v.y = INF;
		} else {
			v.type = 1;
			v.x = height[i];
			v.y = 0;
		}
		
		upd(left[i], right[i], v, 0, n - 1);
	}
 
	for(int i = 0; i < n; ++i)
		finalHeight[i] = query(i, 0, n - 1);
 
	return;
}
