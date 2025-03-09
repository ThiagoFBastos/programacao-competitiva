#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvii = vector<vii>;

typedef long long ll;
typedef unsigned long long ull;

const int maxn = 201;
int n, p[maxn];
double f, dp[maxn][maxn];

int mod(int a, int b) {
	return a >= b ? a - b : a;
}

int query(int L, int R) {
	++L, ++R;
	return L <= R ? p[R] - p[L - 1] : p[n] - p[L - 1] + p[R]; 
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	while(true) {
		cin >> n >> f;
		if(!n) break;

		p[0] = 0;

		for(int i = 1; i <= n; ++i) {
			cin >> p[i];
			p[i] += p[i - 1];
		}

		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				dp[i][j] = INT_MAX;

		for(int i = 0; i < n; ++i)
			dp[i][i] = 0;

		for(int l = 2; l < n; ++l) {
			for(int L = 0; L < n; ++L) {
				int R = mod(L + l - 1, n);
				for(int k = 1, mid = L; k < l; ++k) {
					dp[L][R] = min(dp[L][R], max(query(L, mid), query(mod(mid + 1, n), R)) + dp[L][mid] + dp[mod(mid + 1, n)][R]);
					mid = mod(mid + 1, n);
				}
			}
		}

		for(int L = 0; L < n; ++L) {
			int R = L;
			for(int i = 1; i < n; ++i) {
				dp[0][n - 1] = min(dp[0][n - 1], max(query(L, R), p[n] - query(L, R)) + dp[L][R] + dp[mod(R + 1, n)][mod(L - 1 + n, n)]);
				R = mod(R + 1, n);		
			}
		}

		cout << fixed << setprecision(2) << f * dp[0][n - 1] << '\n';
	}

	return 0;
}