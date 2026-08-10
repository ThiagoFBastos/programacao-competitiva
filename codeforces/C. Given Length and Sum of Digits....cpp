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
 
	int n, m;

	cin >> n >> m;

	vi n1(n), n2(n);
	
	if((m == 0 && n > 1) || 9 * n < m)
		cout << -1 << ' ' << -1 << '\n';

	else if(m == 0)
		cout << "0 0\n";

	else {

		int m1 = m, m2 = m;

		for(int k = 1; k <= 9; ++k) {

			if(k + (n - 1) * 9 >= m) {

				n1[0] = k;
				m1 -= k;

				break;
			}
		}

		for(int k = 9; k >= 1; --k) {

			if(k <= m && k + 9 * (n - 1) >= m) {

				n2[0] = k;
				m2 -= k;

				break;
			}
		}
		
		for(int k = 1; k < n - 1; ++k) {

			for(int i = 0; i <= 9; ++i) {
				
				if(i + 9 * (n - k - 1) >= m1) {

					n1[k] = i;
					m1 -= i;

					break;
				}
			}

			for(int i = 9; i >= 0; --i) {

				if(i <= m2 && i	+ 9 * (n - k - 1) >= m2) {

					n2[k] = i;
					m2 -= i;

					break;
				}
			}
		}

		if(n > 1) {

			n1.back() = m1;
			n2.back() = m2;
		}

		for(int x : n1) 
			cout << x;

		cout << ' ';

		for(int x : n2)
			cout << x;

		cout << '\n';
	}

	return 0;
}
