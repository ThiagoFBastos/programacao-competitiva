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

const int N = 2e3 + 10;

double E[N][N];

void solve() {

	int n, t;
	double p;

	cin >> n >> p >> t;

	for(int i = 0; i <= n; ++i) E[t][i] = i;

	for(int i = t - 1; i >= 0; --i) {
		for(int j = 0; j < n; ++j)
			E[i][j] = (1 - p) * E[i + 1][j] + p * E[i + 1][j + 1];

		E[i][n] = E[i + 1][n];
	}

	cout << fixed << setprecision(9) << E[0][0] << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}

