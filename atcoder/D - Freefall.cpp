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

	i64 A, B;

	cin >> A >> B;

	i64 lo = 0, hi = INFLL / B + 1;

	while(lo < hi) {
		i64 m = (lo + hi) / 2;
		ld f1 = m * B + A / sqrt(m + 1.0L);
		ld f2 = (m + 1) * B + A / sqrt(m + 2.0L);
		if(f1 < f2) hi = m;
		else lo = m + 1;
	}
	
	cout << fixed << setprecision(9) << B * hi + A / sqrt(hi + 1.0L) << '\n';
}	
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	//cin >> t;
    while(t--) solve();
    return 0;
}