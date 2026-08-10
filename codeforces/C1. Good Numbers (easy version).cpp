#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, q, p[10];

	cin >> q;

	p[0] = 1;

	for(int k = 1; k < 10; ++k)
		p[k] = 3 * p[k - 1];

	while(q--) {

		int x = 0;

		cin >> n;

		for(int k = 0; k < 10 && n > x; ++k)
			x += p[k];

		for(int k = 9; k >= 0; --k) {

			if(p[k] < x && x - p[k] >= n)
				x -= p[k];
		}

		cout << x << '\n';
	}

	return 0;
}