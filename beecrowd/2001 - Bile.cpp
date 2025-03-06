#include <bits/stdc++.h>

using namespace std;

#define FOR(k, a, b) for(register int k = (a); k <= (b); ++k)
#define REP(k, a, b) for(register int k = (a); k >= (b); --k)

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

#define MAXN 101
#define MOD 303700049

static ull *M, *M2, *X;
static int n;

static inline void mult();

static inline void square();

static inline void expmod(ll);

static inline void read(long long&);

void mult() {

	int T[MAXN * MAXN];
	register int k = 0, j, i;
		
	for(k ^= k; k < n; ++k) {
	
		for(i ^= i; i < n; ++i) {
		
			ull x = 0;
			
			for(j ^= j; j < n; ++j)
				x += M[k * n + j] * X[i * n + j];
			
			T[k * n + i] = x % MOD;
		}
	}
	
	for(k ^= k; k < n; ++k) {
	
		for(j ^= j; j < n; ++j) {
		
			int i = k * n + j;
			
			M[i] = T[i];
			M2[i] = T[j * n + k];
		}
	}
}

void square() {

	int T[MAXN][MAXN];
	register int k, j, i;
	
	for(k ^= k; k < n; ++k) {
	
		for(i ^= i; i < n; ++i) {
		
			ull x = 0;
			
			for(j ^= j; j < n; ++j)
				x += M[k * n + j] * M2[i * n + j];
			
			T[k][i] = x % MOD;
		}
	}
	
	for(k ^= k; k < n; ++k) {
	
		for(j ^= j; j < n; ++j) {
		
			M[k * n + j] = T[k][j];
			M2[j * n + k] = T[k][j];
		}
	}
}

void expmod(ll p) {

	if(p) {
	
		expmod(p >> 1);
		
		square();
		
		if(p & 1) mult();
		
		return;
	}	
	
	
	FOR(k, 0, n - 1) {
		
		FOR(i, 0, k - 1) {
			
				M[k * n + i] = 0;
				M2[k * n + i] = 0;
			}
			
			M[k * n + k] = 1;
			M2[k * n + k] = 1;
			
			FOR(i, k + 1, n - 1) {
			
				M[k * n + i] = 0;
				M2[k * n + i] = 0;
			}
		}
}

void read(long long& n) {

	register int ch = getchar_unlocked();
	
	while(ch < 48) ch = getchar_unlocked();
	
	n ^= n;
	
	while(ch > 47) {
	
		n = (n << 3) + (n << 1) + ch - 48;
		ch = getchar_unlocked();
	}
}

int main() {
	
	int a[MAXN];
	ll k;
	
	while(scanf("%d%lld", &n, &k) != EOF) {
	
		int sum = 0, N;
		
		N = (n + 1) * (n + 1);
		
		posix_memalign((void**)&M, 64, N * sizeof(ull));
		posix_memalign((void**)&M2, 64, N * sizeof(ull));
		posix_memalign((void**)&X, 64, N * sizeof(ull));
		
		REP(k, n, 1) {
		
			long long x;
			
			read(x);
			
			a[k] = x % MOD;
			
			sum = (0LL + sum + a[k]) % MOD;
		}
			
		a[0] = sum;
		
		X[0] = 1;
		X[1] = 0;
		
		++n;
		
		FOR(k, 1, n - 1) {
		
			X[k * n] = k;
			X[k * n + 1] = k;
		}
		
		FOR(k, 2, n - 1) {
		
			FOR(j, 0, n - 1)
				X[j * n + k] = 0;
				
			X[k * n - n + k] = 1;
		}
		
		expmod(k - n + 1);
	
		ull F = 0, S = 0;
		
		FOR(k, 0, n - 1) {
		
			S += M[k] * a[k];
			F += M[n + k] * a[k];
		}
		
		printf("%llu %llu\n", F % MOD, S % MOD);
		
		free(M);
		free(M2);
		free(X);
	}
	
	return 0;
}