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
	
	int a, b, p, t;
	string s;

	cin >> t;

	while(t--) {

		cin >> a >> b >> p;
		cin >> s;
		
		int i = s.size() - 1;

		s.pop_back();

		vector<ll> c(s.size() + 1);
		c.back() = 0;

		for(int k = (int)s.size() - 1; k >= 0; --k) {

			if(s[k] == 'B') {

				if(s[k] != s[k + 1]) c[k] = c[k + 1] + b;
				else c[k] = c[k + 1];
			}

			else {

				if(s[k] != s[k + 1]) c[k] = c[k + 1] + a;
				else c[k] = c[k + 1];
			}

			if(c[k] <= p)
				i = k;
		}

		cout << i + 1 << '\n';
	}

    return 0;
}

