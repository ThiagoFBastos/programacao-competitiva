#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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
using i128 = __int128;

const int N = 2e5 + 10;

int mb[N], fac[N], p[N], frq[N];
bool composite[N];
bitset<N> check;

void sieve(int n) {
	vector<int> primes;
	for(int i = 2; i <= n; ++i) {
		if(!composite[i]) {
			mb[i] = 1;
			fac[i] = i;
			primes.pb(i);
		}
		for(int p : primes) {
			if(p * i > n) break;
			composite[p * i] = true;
			fac[p * i] = p;
			mb[p * i] = -mb[i];
			if(i % p == 0) {
				mb[p * i] = 0;
				break;
			}
		}
	}
}

vector<int> factors(int x) {
	vector<int> d;
	while(x != 1) {
		int p = fac[x], n = d.size();
		for(int i = 0; i < n; ++i) d.pb(d[i] * p);
		while(fac[x] == p) x /= p;
		d.pb(p);
	}
	return d;
}

void solve() {
	int n;

	cin >> n;

	for(int i = 1; i <= n; ++i) cin >> p[i];

	sieve(n);

	i64 pairs = 0;
	
	for(int g = 2; g <= n; ++g) {
		if(!mb[g]) continue;
		vector<int> f;
		for(int i = g; i <= n; i += g) {
			for(int x : factors(p[i])) {
				if(!check[x]) f.pb(x);
				check[x] = 1;
				pairs += ++frq[x] * mb[x] * mb[g];
			}
		}
		for(int k : f) {
			check[k] = 0;
			frq[k] = 0;
		}
	}

	cout << pairs << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
