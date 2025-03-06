#include <bits/stdc++.h>

using namespace std;

#define FOR(k, a, b) for(register int k = (a); k <= (b); ++k)
#define REP(k, a, b) for(register int k = (a); k >= (b); --k)
#define FORs(k, a, b, s) for(register int k = (a); k <= (b); k += s)

#define all(x) x.begin(), x.end()
#define up(x, y) upper_bound(all(x), y)
#define lower(x, y) lower_bound(all(x), y)
#define INF 0x3ffffff
#define fi first
#define sc second

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

typedef unsigned long long ull;
typedef long long ll;

using VLL = vector<ll>;

#define MAXN 30000000

static vi primes {2};
static bool *is_prime;

static inline VLL divisors(ll);

VLL divisors(ll N) {

	VLL d {1};
	
	if(N < MAXN && is_prime[N]) {
	
		d.push_back(N);
		return d;
	}
	
	if(!(N & 1)) {
	
		ll pmax = N & -N;
		ll p = 1;
		
		while(p < pmax) {
		
			p <<= 1;
			d.push_back(p);
		}
		
		N /= pmax;
	}
	
	register int k;
	int K = primes[1];
	
	for(k = 1; 1LL * K * K <= N; ++k) {
		
		if(N % K == 0) {
		
			ll p = K;
			int n = d.size();
		
			while(N % p == 0) {
				
				FOR(i, 0, n - 1)
					d.push_back(d[i] * p);
			
				p *= K;	
			}
			
			p /= K;
			N /= p;			
		}
		
		K = primes[k + 1];
	}
	
	if(N > 1) {
	
		int n = d.size();
	
		FOR(i, 0, n - 1)
			d.push_back(d[i] * N);
	}
	
	return d;
}

int main() {
	
	is_prime = new bool[MAXN];
	
	memset(is_prime, -1, MAXN * sizeof(bool));
	
	primes.reserve(1857860);
	
	FORs(k, 4, MAXN, 2)
		is_prime[k] = false;
		
	FORs(k, 3, MAXN, 2) {
	
		if(is_prime[k]) {
		
			int j = k << 1;
			
			FORs(i, j + k, MAXN, j)
				is_prime[i] = false; 

			primes.push_back(k);
		}
	}
	
	primes.push_back(MAXN + 1);
	
	ll N;
	
	while(scanf("%lld", &N) != EOF) {
	
		if(N < 2)
			puts("1");
			
		else {
		
			VLL divisores = divisors(N);
		
			int n = divisores.size();
		
			int count = 0;
			
			FOR(k, 0, n - 1) {
			
				ll X = divisores[k], Y, a, b;
		
				Y = N / X;
				X <<= 1;
			
				a = X + Y >> 1;
				b = max(X, Y) - a;
				
				if(llabs(b - a) + 1 == min(X, Y)) ++count;
			}
			
			printf("%d\n", count);
		}
	}
	
	
	return 0;
}