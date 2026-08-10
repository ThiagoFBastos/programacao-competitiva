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

	int t, ct[201];

	cin >> t;

	while(t--) {

		int n;

		cin >> n;

		for(int k = 1; k <= 2 * n; ++k)
			ct[k] = -1;

		vi b(n), a(2 * n, -1);

		for(int k = 0; k < n; ++k) {

			cin >> b[k];

			a[2 * k] = b[k];

			ct[b[k]] = 2 * k;			
		}
		
		bool p = true;

		for(int k = 0; k < n; ++k) {

			for(int i = b[k] + 1; i <= 2 * n; ++i) {

				if(ct[i] == -1) {

					ct[i] = 1 + ct[b[k]];
					a[ct[i]] = i;

					break;
				}
			}

			if(a[ct[b[k]] + 1] == -1) {

				p = false;

				break;	
			}
		}

		if(p) {

			for(int k = 0; k < (int)a.size() - 1; ++k) cout << a[k] << ' ';
			cout << a.back() << '\n';
		}

		else
			cout << -1 << '\n';
	}


    return 0;
}

