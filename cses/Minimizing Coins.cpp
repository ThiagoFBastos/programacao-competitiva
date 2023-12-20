#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, c[MAXN], *q;
	cin >> n >> m;
	q = new int[m + 1];
	for(int k = 0; k <= m; ++k) q[k] = 1e7;
	q[0] = 0;
	for(int i = 0; i < n; ++i) cin >> c[i];
	sort(c, c + n);
	for(int i = 1; i <= m; ++i)
		for(int j = 0; j < n && i - c[j] >= 0; ++j)
			q[i] = min(q[i], 1 + q[i - c[j]]);
	if(q[m] == 1e7) cout << -1 << '\n';
	else cout << q[m] << '\n';
	return 0;
} 
