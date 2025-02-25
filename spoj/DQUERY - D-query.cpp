#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
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
using i128 = __int128;

inline i64 hilbertOrder(int x, int y, int pow, int rotate = 0) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	i64 subSquareSize = 1ll << (2*pow - 2);
	i64 ans = seg * subSquareSize;
	i64 add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

const int N = 1e6 + 10;

int frq[N], cnt;

void add(int x) {
	cnt += frq[x]++ == 0;
}

void rem(int x) {
	cnt -= --frq[x] == 0;
}

struct query {
	int l, r, pos;
	i64 val;
};

bool operator<(const query& q1, const query& q2) {
	return q1.val < q2.val;
}

void solve() {
	int n, q;
	cin >> n;
	vector<int> a(n);
	for(int& v : a) cin >> v;
	cin >> q;
	vector<query> queries(q);
	vector<int> ans(q);
	for(int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		--l, --r;
		queries[i] = {l, r, i, hilbertOrder(l, r, 19)};
	}
	sort(all(queries));
	int lo = 0, hi = -1;
	for(auto& x : queries) {
		int l = x.l, r = x.r, pos = x.pos;
		while(hi < r) add(a[++hi]);
		while(hi > r) rem(a[hi--]);
		while(lo < l) rem(a[lo++]);
		while(lo > l) add(a[--lo]);
		ans[pos] = cnt;
	}
	for(int v : ans) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}