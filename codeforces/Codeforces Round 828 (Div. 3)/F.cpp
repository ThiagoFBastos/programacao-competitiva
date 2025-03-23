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

i64 sum(int l, int r) {
	return (l + r) * (r - l + 1ll) / 2;
}

void solve() {
/*
	tem 0
	
	0 1 2 3 ... x - 1

	mex = 7

	0 1 2 3 4 5 6 8 9 10 11
				
	tamanho do intervalo <= 2 * mex
*/
	int n;

	cin >> n;

	vector<int> pos(n + 1, -1), max_pos(n + 1, -1), min_pos(n + 1, -1);

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		pos[a] = i;
	}

	max_pos[0] = min_pos[0] = pos[0];

	for(int i = 1; i < n; ++i) {
		max_pos[i] = max(pos[i], max_pos[i - 1]);
		min_pos[i] = min(pos[i], min_pos[i - 1]);
	}

	i64 cnt = 0;

	for(int mex = 1; mex <= n; ++mex) {
		int l = min_pos[mex - 1], r = max_pos[mex - 1];
		int L = 0, R = n - 1;

		if(r - l + 1 > 2 * mex || (pos[mex] >= l && pos[mex] <= r)) continue;

		if(pos[mex] > r) R = pos[mex] - 1;
		else L = pos[mex] + 1;

		L = max(L, r - 2 * mex + 1);
		R = min(R, l + 2 * mex - 1);
		
		int lo = L, hi = l;

		while(lo < hi) {
			int mid = (lo + hi) / 2;
			if(R - mid + 1 <= 2 * mex) hi = mid;
			else lo = mid + 1;
		}
		
		int m = l - hi + 1;
		
		cnt += m * (R + 1ll) - sum(hi, l);
		cnt -= m * (r + 0ll) - sum(hi, l);
		cnt += 2 * mex * (hi - L + 0ll);
		cnt -= (hi - L + 0ll) * r - sum(L, hi - 1);
	}

	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
