#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MOD 1000000007
#define MAXN 1000000
int expmod(int a, int p) {
	if(p == 0) return 1;
	int r = expmod(a, p >> 1);
	r = 1LL * r * r % MOD;
	return p & 1 ? 1LL * r * a % MOD : r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int *fm = new int[MAXN + 1];
	fm[0] = fm[1] = 1;
	for(int k = 2; k <= MAXN; ++k) fm[k] = 1LL * k * fm[k - 1] % MOD;
	int n;
	cin >> n;
	while(n--) {
		int a, b;
		cin >> a >> b;
		cout << 1LL * fm[a] * expmod(1LL * fm[b] * fm[a - b] % MOD, MOD - 2) % MOD << '\n';
	}
	return 0;
}
