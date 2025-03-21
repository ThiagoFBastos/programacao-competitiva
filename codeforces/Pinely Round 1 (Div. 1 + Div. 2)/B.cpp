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

	map<int, int> frq;

	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		++frq[v];
	}
	
	if((int)frq.size() != 2) cout << n << '\n';
	else cout << (n - 2) / 2 + 2 << '\n';
}	

int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


