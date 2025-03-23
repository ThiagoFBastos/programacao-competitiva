#pragma GCC optimize("O3,unroll-loops")

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

const int N = 1e5 + 100;

ld F[N];

void solve() {
	int n;

	cin >> n;

	cout << fixed << setprecision(4) << 1 - F[n] << '\n';
}

int main() {

	F[2] = 1.0;
	F[4] = 0.5;

	for(int k = 6; k < N; k += 2) {
		i64 P = (k - 3ll) * (k - 2ll) / 2;
		i64 Q = 2 * (k / 2 - 1ll) * (k / 2 - 1);
		F[k] = ld(P) / Q * F[k - 2];
	}

    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}

