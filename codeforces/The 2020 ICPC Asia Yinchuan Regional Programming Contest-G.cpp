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

i64 g(int a, int b) {
	a -= b;
	return (i64)a * a;
}

i64 f(vector<int>& h, vector<int>& p) {
	i64 order = 0, ans = 0;
	int n = h.size();

	vector<int> nxt(n, -1), prv(n, -1);

	for(int i = 0; i < n - 1; ++i) nxt[i] = i + 1;
	for(int i = n - 1; i; --i) prv[i] = i - 1;

	for(int i = 1; i < n; ++i) order += g(h[i], h[i - 1]);

	ans += order;

	for(int i = n - 1; i; --i) {
		int k = p[i];
		if(nxt[k] != -1 && prv[k] != -1) {
			order -= g(h[k], h[nxt[k]]);
			order -= g(h[k], h[prv[k]]);
			order += g(h[prv[k]], h[nxt[k]]);
			prv[nxt[k]] = prv[k];
			nxt[prv[k]] = nxt[k];
		} else if(nxt[k] != -1) {
			order -= g(h[k], h[nxt[k]]);
			prv[nxt[k]] = -1;
		} else if(prv[k] != -1) {
			order -= g(h[k], h[prv[k]]);
			nxt[prv[k]] = -1;
		}
		ans += order;
	}

	return ans;
}

void shift(vector<int>& p, int k) {	
	int n = p.size();
	vector<int> tmp(n);
	for(int i = 0; i < n; ++i) tmp[i] = p[(i + k) % n];
	swap(tmp, p);
}

void solve() {
	int n, q;
	i64 lastans = 0;

	cin >> n >> q;

	vector<int> h(n), p(n);

	for(int& v : h) cin >> v;

	for(int& v : p) {
		cin >> v;
		--v;
	}
	
	cout << (lastans = f(h, p)) << '\n';

	while(q--) {
		int k;
		cin >> k;
		shift(p, (k + lastans) % n);
		cout << (lastans = f(h, p)) << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
 
