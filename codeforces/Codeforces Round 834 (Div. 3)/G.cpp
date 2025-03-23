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

const int N = 8e5 + 100;

int pre[N], st[N], lazy[N];

void build(int l, int r, int p = 1) {
	lazy[p] = 0;
	if(l == r) {
		st[p] = pre[l];
		return;
	}
	int m = (l + r) / 2;
	build(l, m, 2 * p);
	build(m + 1, r, 2 * p + 1);
	st[p] = min(st[2 * p], st[2 * p + 1]);
}

void push(int p) {
	for(int k : {2*p,2*p+1}) {
		st[k] += lazy[p];
		lazy[k] += lazy[p];
	}
	lazy[p] = 0;
}

void upd(int l, int r, int x, int lo, int hi, int p = 1) {
	if(l > r || lo > hi || r < lo || l > hi) return;
	else if(lo >= l && hi <= r) {
		st[p] += x;
		lazy[p] += x;
		return;
	}
	int m = (lo + hi) / 2;
	push(p);
	upd(l, r, x, lo, m, 2 * p);
	upd(l, r, x, m + 1, hi, 2 * p + 1);
	st[p] = min(st[2 * p], st[2 * p + 1]);
}

int query(int lo, int hi, int p = 1) {
	if(lo == hi) return lo;
	push(p);
	int m = (lo + hi) / 2;
	if(st[2 * p + 1] >= 1) return query(lo, m, 2 * p);
	return query(m + 1, hi, 2 * p + 1);
}

void solve() {

	int n;

	cin >> n;

	n /= 2;

	vector<int> b(n), A;
	set<int> a;

	memset(pre, 0, (2*n + 1) * sizeof(int));

	bool ok = true;

	for(int i = 0; i < n; ++i) {
		cin >> b[i];
		ok = ok && pre[b[i]] == 0;
		pre[b[i]] = -1;
	}

	if(!ok) {
		cout << "-1\n";
		return;
	}

	for(int i = 1; i <= 2 * n; ++i) {
		if(!pre[i]) {
			pre[i] = 1;
			a.insert(i);
		}
	}

	for(int i = 1; i <= 2*n; ++i) pre[i] += pre[i - 1];

	build(1, 2*n);

	for(int i = 0; i < n; ++i) {
		upd(b[i], 2*n, 1, 1, 2 * n);

		int k = query(1, 2*n);
		auto it = a.lower_bound(k);
		
		if(it == a.end()) {
			cout << "-1\n";
			return;
		}
		
		upd(*it, 2*n, -1, 1, 2*n);

		if(*it < b[i]) A.pb(*it), A.pb(b[i]);
		else A.pb(b[i]), A.pb(*it);
			
		a.erase(it);
	}

	for(int i = 0; i < n; ++i) {
		if(b[i] != max(A[2 * i], A[2 * i + 1])) {
			cout << "-1\n";
			return;
		}
	}

	for(int x : A) cout << x << ' ';
	cout << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


