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
using i128 = __int128;

const int N = 5e3 + 10;

bitset<N> pre[N], suf[N];

void solve() {
	int n, m;

	cin >> n >> m;

	vector<int> a(n);
	
	for(int& v : a) {
		cin >> v;
		v = min(v, m);
	}

	pre[0][0] = suf[n + 1][0] = 1;

	for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] | (pre[i - 1] << a[i - 1]);
	for(int i = n; i >= 1; --i) suf[i] = suf[i + 1] | (suf[i + 1] << a[i - 1]);

	int cnt = 0;

	for(int i = 1; i <= n; ++i) {
		int k = m, nec = 0;
		for(int j = 0; j < m; ++j) {
			if(!pre[i - 1][j]) continue;
			while(k >= 0 && (k + j >= m || !suf[i + 1][k])) --k;	
			nec = nec || k + j >= m - a[i - 1];
		}
		cnt += !nec;
	}

	cout << cnt << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

