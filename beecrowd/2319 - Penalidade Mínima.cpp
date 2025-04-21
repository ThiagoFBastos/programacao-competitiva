#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
#define f first
#define s second
typedef long long ll;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
void get(int n, int& a, int& b) {
	a = 0;
	b = 0;
	while(!(n & 1)) ++a, n >>= 1;
	while(n % 5 == 0) ++b, n /= 5;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll **dp1, **dp2;
	int n;
	cin >> n;
	dp1 = new ll*[n];
	dp2 = new ll*[n];
	for(int i = 0; i < n; ++i) {
		dp1[i] = new ll[n];
		dp2[i] = new ll[n];
		for(int j = 0; j < n; ++j) {
			int x;
			cin >> x;
			if(x) {
				int a, b;
				get(x, a, b);
				dp1[i][j] = a;
				dp2[i][j] = b;
			}
			else
				dp1[i][j] = dp2[i][j] = INT_MAX;
		}
	}
	for(int k = n - 1; k >= 0; --k) {
		for(int i = n - 1; i >= 0; --i) {
			if(i < n - 1 && k < n - 1) {
				dp1[k][i] += min(dp1[k + 1][i], dp1[k][i + 1]);
				dp2[k][i] += min(dp2[k + 1][i], dp2[k][i + 1]);
			}
			else if(i < n - 1) {
				dp1[k][i] += dp1[k][i + 1];
				dp2[k][i] += dp2[k][i + 1];
			}
			else if(k < n - 1) {
				dp1[k][i] += dp1[k + 1][i];
				dp2[k][i] += dp2[k + 1][i];
			}
		}
	}
	cout << min(dp1[0][0], dp2[0][0]) << '\n';
	return 0;
}