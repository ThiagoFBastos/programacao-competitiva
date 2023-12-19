#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
#define MAXN 1000000
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	vi f(MAXN + 1, 1);
 
	for(int k = 2; k <= MAXN; k += 2)
		f[k] += __builtin_ctz(k);
	
	for(int k = 3; k <= MAXN; k += 2) {
 
		if(f[k] == 1) {
 
			for(int i = k; i <= MAXN; i += k) {
 
				int N = i, d = 1;
 
				while(N % k == 0) {
 
					N /= k;
					++d;
				}
 
				f[i] *= d;
			}
		}
	}
 
	cin >> t;
 
	while(t--) {
		int n;
		cin >> n;
		cout << f[n] << '\n';
	}
 
    return 0;
}
