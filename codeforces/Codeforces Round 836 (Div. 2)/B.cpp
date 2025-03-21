#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
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

void solve() {
	
	int n;

	cin >> n;

	if(n % 2) {
		for(int i = 0; i < n; ++i) cout << 1 << ' ';
		cout << '\n';
	} else {
		int k = 2;
		while((1ll * k * n - 1) % (n - 1)) ++k;
		for(int i = 0; i < n - 1; ++i) cout << (1ll * k * n - 1) / (n - 1) << ' ';
		cout << "1\n"; 	
	}
}

 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}
