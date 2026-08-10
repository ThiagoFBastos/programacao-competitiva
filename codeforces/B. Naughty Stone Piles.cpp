#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

#define MAXN 100000

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;

	cin >> n;

	vi x(n);
	vector<ll> preffix(n + 1);

	for(int k = 0; k < n; ++k)
		cin >> x[k];

	sort(x.begin(), x.end(), greater<int>());
	
	preffix[0] = 0;

	for(int k = 1; k <= n; ++k)
		preffix[k] = preffix[k - 1] + x[k - 1];
		
	ll ans[MAXN + 1];

	for(int k = 1; k <= MAXN; ++k) {

		ll p = 1;

		ans[k] = 0;

		for(ll i = 1, j = 1; i <= n; i += p, ++j) {
			p *= k;
			ans[k] += j * (preffix[min(n + 0LL, i + p)] - preffix[i]);
		}
	}

	int queries, k;

	cin >> queries;

	while(queries-- > 1) {
		cin >> k;
		cout << ans[k] << ' ';
	}

	cin >> k;
	cout << ans[k] << '\n';


	return 0;
}