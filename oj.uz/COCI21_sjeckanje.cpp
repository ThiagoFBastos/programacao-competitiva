#include "bits/stdc++.h"
 
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
 
const int N = 2e5 + 100, M = 1 << 19;
 
struct TYPE {
	i64 dp[3][3];
	TYPE() {
		for(int a : {0,1,2})
		for(int b : {0,1,2})
			dp[a][b] = -INFLL;
	}
};
 
i64 lazy[M];
TYPE st[M];
int n, q, a[N];
 
TYPE merge(TYPE l, TYPE r) {
	TYPE ans;
		
	for(int a : {0,1,2})
	for(int b : {0,1,2})
	for(int c : {0,1,2})
		ans.dp[a][c] = max(ans.dp[a][c], l.dp[a][b] + r.dp[b][c]);
 
	return ans;
}
 
/*
	0 -> -1 -> subtraí
	1 ->  0 -> não fiz nada
	2 ->  1 -> somei
*/
 
void build(int l, int r, int k = 1) {
	if(l == r) {
		
		// tinha subtraido e agora somo -> tanto faz o que vem depois
		st[k].dp[0][1] = a[l];
 
		// tinha subtraido e agora não faco nada -> ainda preciso somar
 
		st[k].dp[0][0] = 0;
 
		// tinha somado e agora subtraio -> tanto faz o que vem depois
		st[k].dp[2][1] = -a[l];
 
		// tinha somado e agora não faço nada -> ainda preciso subtrair
		st[k].dp[2][2] = 0;
 
		// não tinha feito nada e subtrai -> preciso somar depois
 
		st[k].dp[1][0] = -a[l];
		
		// não tinha feito nada e somei -> preciso subtrair depois
 
		st[k].dp[1][2] = a[l];
 
		// não tinha feito nada e não fiz nada -> tanto faz o que vem depois
 
		st[k].dp[1][1] = 0;
	} else {
		int m = (l + r) / 2;
		build(l, m, 2 * k);
		build(m + 1, r, 2 * k + 1);
		st[k] = merge(st[2 * k], st[2 * k + 1]);
	}
}
 
/*
	entrou com x e saiu com x -> + nada
	entrou com +1 e saiu com -1 -> -2x
	entrou com -1 e saiu com +1 -> +2x
	entrou com nada e saiu com -1 -> -x
	entrou com nada e saiu com +1 -> +x
	entrou com -1 e saiu com nada -> +x
	entroi com +1 e saiu com nada -> -x
*/
 
void apply(int i, int j, i64& res, i64 x) {
	int sig[] = {-1, 0, 1};
	if(i == j) return;
	else if(i != 1 && j != 1) res += 2 * x * sig[j];		
	else res += x * (j != 1 ? sig[j] : -sig[i]);
} 
 
void push(int k) {
	if(!lazy[k]) return;
	for(int i : {2 * k, 2 * k + 1}) {
		lazy[i] += lazy[k];
		for(int x : {0,1,2})
		for(int y : {0,1,2})
			apply(x, y, st[i].dp[x][y], lazy[k]);
	}	
	lazy[k] = 0;
}
 
void upd(int l, int r, int x, int lo, int hi, int k = 1) {
	if(l > r || lo > hi || r < lo || l > hi) return;
	else if(lo >= l && hi <= r) {
		lazy[k] += x;
		for(int i : {0,1,2})
		for(int j : {0,1,2})
			apply(i, j, st[k].dp[i][j], x);
	} else {
		int m = (lo + hi) / 2;
		push(k);
		upd(l, r, x, lo, m, 2 * k);
		upd(l, r, x, m + 1, hi, 2 * k + 1);
		st[k] = merge(st[2 * k], st[2 * k + 1]);
	}
}
 
void solve() {
	cin >> n >> q;
 
	for(int i = 0; i < n; ++i) cin >> a[i];
 
	build(0, n - 1);
 
	while(q--) {
		int l, r, x;
 
		cin >> l >> r >> x;
 
		--l, --r;
 
		upd(l, r, x, 0, n - 1);
	
		cout << st[1].dp[1][1] << '\n';
	}
}	
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
