#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100000
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, sheets[MAXN + 1], book[MAXN][2];
	cin >> n >> m;
	for(int i = 0; i < n; ++i) cin >> book[i][0];
	for(int i = 0; i < n; ++i) cin >> book[i][1];
	for(int i = 0; i <= m; ++i) sheets[i] = -1;
	sheets[0] = 0;
	for(int i = 0; i < n; ++i) {
		int p = book[i][0], s = book[i][1];
		for(int k = m - p; k >= 0; --k) {
			if(sheets[k] != -1)
				sheets[k + p] = max(sheets[k + p], sheets[k] + s);
		}
	}
	cout << max(0, *max_element(sheets, sheets + m + 1)) << '\n';
	return 0;
} 
