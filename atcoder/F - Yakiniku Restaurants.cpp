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

const int N = 5e3 + 10, M = 210;

int b[N][M], n, m;
i64 a[N];
vector<tuple<int, int, int>> best[M];

i64 st[4 * N], lazy[4 * N];

void push(int no) {
	if(!lazy[no]) return;
	int k[2] = {2*no,2*no+1};
	for(int i : {0,1}) {
		lazy[k[i]] += lazy[no];
		st[k[i]] += lazy[no];
	}
	lazy[no] = 0;
}

void upd(int l, int r, i64 x, int lo, int hi, int n = 1) {
	if(l > r || r < lo || l > hi) return;
	else if(lo >= l && hi <= r) {
		st[n] += x;
		lazy[n] += x;
	} else {
		int m = (lo + hi) / 2;
		push(n);
		upd(l, r, x, lo, m, 2 * n);
		upd(l, r, x, m + 1, hi, 2 * n + 1);
		st[n] = max(st[2 * n], st[2 * n + 1]);
	}
}

i64 query(int l, int r, int lo, int hi, int n = 1) {
	if(l > r || r < lo || l > hi) return 0;	
	else if(lo >= l && hi <= r) return st[n];
	int m = (lo + hi) / 2;
	push(n);
	i64 p1 = query(l, r, lo, m, 2 * n);
	i64 p2 = query(l, r, m + 1, hi, 2 * n + 1);
	return max(p1, p2);
}

void solve() {

	cin >> n >> m;

	for(int i = 1; i < n; ++i) {
		cin >> a[i];
		a[i] += a[i - 1];
	}

	for(int i = 0; i < n; ++i)
	for(int j = 0; j < m; ++j)
		cin >> b[i][j];

	i64 ans = 0;

	for(int i = 0; i < n; ++i) {
		upd(i, i, a[i], 0, n - 1);

		for(int j = 0; j < m; ++j) {
			auto& X = best[j];
			int len = 1;

			while(!X.empty() && get<0>(X.back()) < b[i][j]) {
				auto [x, k, l] = X.back();
				X.pop_back();
				len += l;
				upd(k - l + 1, k, b[i][j] - x, 0, n - 1);
			}

			upd(i, i, b[i][j], 0, n - 1);

			X.pb({b[i][j], i, len});
		}

		ans = max(ans, query(0, i, 0, n - 1) - a[i]);
	}

	cout << ans << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
