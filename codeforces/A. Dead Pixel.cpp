#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2")

using namespace std;

#define f first
#define s second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define up(x, v) upper_bound(all(x), v)
#define low(x, v) lower_bound(all(x), v)
#define bin(x, v) binary_search(all(x), v)
#define FOR(k, a, b) for(int k = (a); k < (b); ++k)
#define ROF(k, a, b) for(int k = (a); k > (b); --k)
#define fn(k, n) for(int k = 0; k < n; ++k)

#define EPS 1.0e-9

#define X real()
#define Y imag()

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using point = pair<double, double>;
using Vector = complex<double>;

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;

	cin >> t;

	while(t--) {

		int a, b, x, y;

		cin >> a >> b >> x >> y;

		int A = 0;

		if(x)
			A = x * b;

		if(x < a - 1)
			A = max(A, b * (a - x - 1));

		if(y)
			A = max(A, a * y);

		if(y < b - 1)
			A = max(A, a * (b - y - 1));

		cout << A << '\n';
	}

    return 0;
}
 