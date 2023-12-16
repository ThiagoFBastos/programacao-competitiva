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
 
const int N = 1 << 19;
const i64 MOD = 687579270059206813, B = 8762099909;
 
i64 st[2][N], powt[N];
string s;
int n, q;
 
void build(i64 st[], string& s, int l, int r, int p = 1) {
	if(l == r) {
		st[p] = s[l] - 'a' + 1;
		return;
	}
 
	int m = (l + r) / 2;
 
	build(st, s, l, m, 2 * p);
	build(st, s, m + 1, r, 2 * p + 1);
 
	st[p] = (st[2 * p] + (__int128)powt[m - l + 1] * st[2 * p + 1]) % MOD;
}
 
void upd(i64 st[], int k, char x, int l, int r, int p = 1) {
	if(l == r) {
		st[p] = x - 'a' + 1;
		return;
	}
	int m = (l + r) / 2;
	if(k <= m) upd(st, k, x, l, m, 2 * p);
	else upd(st, k, x, m + 1, r, 2 * p + 1);
	st[p] = (st[2 * p] + (__int128)powt[m - l + 1] * st[2 * p + 1]) % MOD;
}
 
i64 query(i64 st[], int l, int r, int lo, int hi, int p = 1) {
	if(l > r || lo > hi || r < lo || l > hi) return 0;
	else if(lo >= l && hi <= r) return st[p];
	int m = (lo + hi) / 2;
	i64 h1 = query(st, l, r, lo, m, 2 * p);
	i64 h2 = query(st, l, r, m + 1, hi, 2 * p + 1);
	if(l <= m && r > m) h2 = (__int128)powt[m - max(lo, l) + 1] * h2 % MOD;
	return (h1 + h2) % MOD;
}
 
void solve() {
	cin >> n >> q >> s;
 
	powt[0] = 1;
	for(int i = 1; i < N; ++i) powt[i] = (__int128)B * powt[i - 1] % MOD;
 
	build(st[0], s, 0, n - 1);	
 
	reverse(all(s));
 
	build(st[1], s, 0, n - 1);
 
	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int p;
			char c;
			cin >> p >> c;
			--p;
			upd(st[0], p, c, 0, n - 1);
			upd(st[1], n - p - 1, c, 0, n - 1);
		} else {
			int l, r;
			cin >> l >> r;
			--l, --r;
			i64 h1 = query(st[0], l, r, 0, n - 1);
			i64 h2 = query(st[1], n - r - 1, n - l - 1, 0, n - 1);
			cout << (h1 == h2 ? "YES\n" : "NO\n");
		}
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
