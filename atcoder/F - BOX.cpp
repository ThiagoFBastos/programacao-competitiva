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

const int N = 3e5 + 100;
vector<int> S[N];
int name[N], inv[N], who[2 * N];

void solve() {
	int n, q;

	cin >> n >> q;

	for(int i = 1; i <= n; ++i) {
		name[i] = i;
		inv[i] = who[i] = i;
		S[i].pb(i);
	}

	while(q--) {
		int t, x, y;
		
		cin >> t >> x;
		
		if(t == 1) {
			cin >> y;

			swap(x, y);
			
			if(S[x].size() > S[y].size()) {
				swap(name[x], name[y]);
				swap(inv[name[x]], inv[name[y]]);
				swap(S[x], S[y]);
			}
		
			for(int b : S[x]) {
				who[b] = name[y];
				S[y].pb(b);
			}
			
			S[x].clear();

		} else if(t == 2) {
			who[++n] = name[x];
			S[x].pb(n);
		} else
			cout << inv[who[x]] << '\n';
	}
}	
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	//cin >> t;
    while(t--) solve();
    return 0;
}
