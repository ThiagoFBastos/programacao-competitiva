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
#define MOD 1000000007
int expmod(int n, int p, int mod) {
	int r = 1;
	while(p > 0) {
		if(p & 1) r = 1LL * r * n % mod;
		n = 1LL * n * n % mod;
		p >>= 1; 
	}
	return r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int a, b, c;
		cin >> a >> b >> c;
		cout << expmod(a, expmod(b, c, MOD - 1), MOD) << '\n';
	}
	
    return 0;
}
