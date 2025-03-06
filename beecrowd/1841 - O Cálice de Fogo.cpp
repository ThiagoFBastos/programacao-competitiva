#include <bits/stdc++.h>

using namespace std;

#define MAXN 10000000

using vi = vector<int>;
using ull = unsigned long long;

#define MOD 1000000007

static int expmod(int n, int p) {

	if(p == 0) return 1;
	
	int ans = expmod(n, p / 2);
	
	ans = 1LL * ans * ans % MOD;
	
	return p & 1 ? 1LL * ans * n % MOD : ans;
}

class FenwickTree {

	vi ft;
	int n;
	
	public:
	
		FenwickTree(int N) {
		
			n = N;
			ft.assign(N + 1, 1);	
		}

		void update(int k, int v) {
			
			while(k <= n) {
			
				ft[k] = (1LL * ft[k] * v) % MOD;
				k += k & -k;
			}
		}
		
		int query(int k) {
		
			int ans {1};
			
			while(k > 0) {
			
				ans = (1LL * ans * ft[k]) % MOD;
				k -= k & -k;
			}
			
			return ans;
		}
};

int main() {

	ull N;
	int *power {new int[MAXN + 1]};
	
	for(int k = 0; k <= MAXN; ++k)
		power[k] = 1;
	
	scanf("%llu", &N);
	
	FenwickTree ft(MAXN);

	if(!(N & 1)) {
		
		while(!(N & 1)) {
		
			N >>= 1;
			++power[2];
		}
		
		ft.update(2, power[2]);
	}
	
	for(unsigned k = 3; 1LLU * k * k <= N; k += 2) {
	
		if(N % k == 0) {
	
			while(N % k == 0) {
			
				N /= k;
				++power[k];
			}
			
			ft.update(k, power[k]);
		}
	}
	
	if(N > 1 && N < MAXN) {
	
		++power[N];
		ft.update(N, power[N]);
	}
	
	int p;
	
	while(scanf("%d", &p) != EOF) {
	
		++power[p];
		
		ft.update(p, 1LL * power[p] * expmod(power[p] - 1, MOD - 2) % MOD);
		printf("%d\n",	ft.query(p - 1));
	}
	
	return 0;
}