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
	int l, r, x, a, b;

	cin >> l >> r >> x >> a >> b;

	if(a == b) cout << "0\n";
	else if(b < l || b > r) cout << "-1\n";
	else if(abs(a - b) >= x) cout << "1\n";
	else if(abs(l - r) < x) cout << "-1\n"; 
	else if(min(abs(a - l), abs(l - b)) >= x || min(abs(a - r), abs(r - b)) >= x) cout << "2\n";
	else if(min(abs(a - l), abs(r - b)) >= x || min(abs(a - r), abs(l - b)) >= x) cout << "3\n";
	else cout << "-1\n";
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


