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

const int N = 2e5 + 10, B = 448;

struct query {
	int l, r, id;
};

bool operator<(const query& q1, const query& q2) {
	return ii(q1.l / B, q1.r) < ii(q2.l / B, q2.r);
}

query queries[N];
i64 ans[N], triples;
int frq[N], a[N];

void add(int x) {
	triples += frq[x] * (frq[x] - 1ll) / 2;
	++frq[x];
}

void rem(int x) {
	--frq[x];
	triples -= frq[x] * (frq[x] - 1ll) / 2;
}

void solve() {
	int n, q;

	cin >> n >> q;

	for(int i = 0; i < n; ++i) cin >> a[i];

	for(int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		--l, --r;
		queries[i] = {l, r, i};
	}

	sort(queries, queries + q);

	int lo = 0, hi = -1;

	for(int i = 0; i < q; ++i) {
		auto [l, r, id] = queries[i];
		while(hi < r) add(a[++hi]);
		while(hi > r) rem(a[hi--]);
		while(lo < l) rem(a[lo++]);
		while(lo > l) add(a[--lo]);
		ans[id] = triples;
	}

	for(int i = 0; i < q; ++i) cout << ans[i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}

