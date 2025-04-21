#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

const int maxn = 1001;

int a[maxn][maxn], h[maxn][maxn], p[maxn][maxn], good[maxn][maxn], r, c;

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> r >> c;

	for(int i = 1; i <= r; ++i)
		for(int j = 1; j <= c; ++j)
			cin >> a[i][j];
	
	for(int i = 1; i < r; ++i) {
		for(int j = 1; j < c; ++j) {
			if(a[i][j] + a[i + 1][j + 1] <= a[i][j + 1] + a[i + 1][j])
				good[i][j] = 1;
		}
	}

	for(int i = 1; i <= r; ++i) good[i][c] = 1;
	for(int i = 1; i <= c; ++i) good[r][i] = 1;
 
	for(int i = 1; i <= r; ++i)
		for(int j = 1; j <= c; ++j)
			p[i][j] = -good[i][j] & (p[i][j - 1] + good[i][j]);
	
	for(int j = 1; j <= c; ++j) {
		stack<ii> S;
		for(int i = r; i; --i) {
			while(!S.empty() && S.top().first >= p[i][j]) S.pop();
			h[i][j] = S.empty() ? r : S.top().second;
			S.push({p[i][j], i});
		}
		while(!S.empty()) S.pop();
		for(int i = 1; i <= r; ++i) {
			while(!S.empty() && S.top().first >= p[i][j]) S.pop();
			h[i][j] -= (S.empty() ? 1 : S.top().second + 1) - 1;
			S.push({p[i][j], i});
		}
		
	}
	
	int ans = 0;

	for(int i = 1; i <= r; ++i)
		for(int j = 1; j <= c; ++j)
			ans = max(ans, (p[i][j] + (j < c))  * h[i][j]);

	cout << ans << '\n';
	return 0;
}