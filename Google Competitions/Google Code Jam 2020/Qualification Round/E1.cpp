#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
static int m[50][50], ans[50][50], n, k;
static bitset<51> rows[50], cols[50];
static bool backtrack(int r, int c, int trace = 0);
bool backtrack(int r, int c, int trace) {
	if(c == n) ++r, c = 0;
	if(r == n) {
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				ans[i][j] = m[i][j];
		return true;
	}
	else {
		if(r == c) {
			register int low = n, high;
			while(low && trace + low + (n - r - 1) * n >= k) --low;
			high = ++low;
			while(high <= n && trace + high <= k) ++high;
			--high;
			while(low <= high) {
				if(!(rows[r][low] || cols[c][low])) {
					rows[r][low] = cols[c][low] = 1;
					m[r][c] = low;
					if(backtrack(r, c + 1, trace + low)) 
						return true;
					rows[r][low] = cols[c][low] = 0;
				}
				++low;
			}
		}
		else {
			for(register int i = 1; i <= n; ++i) {
				if(!(rows[r][i] || cols[c][i])) {
					rows[r][i] = cols[c][i] = 1;
					m[r][c] = i;
					if(backtrack(r, c + 1, trace)) 
						return true;
					rows[r][i] = cols[c][i] = 0;
				}
			}
		}
	}
	return false;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
 	int t;
	cin >> t;
	for(int c = 1; c <= t; ++c) {
		cin >> n >> k;
		for(int i = 0; i < n; ++i) {
			cols[i].reset();
			rows[i].reset();
		}
		cout << "Case #" << c << ": ";
		if(k != n + 1 && k != n * n - 1 && backtrack(0, 0)) {
			cout << "POSSIBLE\n";
			for(int i = 0; i < n; ++i) {
				for(int j = 0; j < n - 1; ++j) cout << ans[i][j] << ' ';
				cout << ans[i][n - 1] << '\n';
			}
		}
		else cout << "IMPOSSIBLE\n";
	}
	return 0;
}