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
	int n, q;

	cin >> n;

	vector<i64> a(n);
	vector<int> t(n, 0);
	i64 X = 0, T = -1;

	for(i64& v : a) cin >> v;
	
	cin >> q;

	for(int i = 1; i <= q; ++i) {
		int tp, x;
		cin >> tp >> x;
		if(tp == 1) X = x, T = i;
		else if(tp == 2) {
			int y;
			cin >> y;
			--x;
			if(t[x] < T) a[x] = 0;
			t[x] = i;
			a[x] += y;
		} else {
			--x;
			if(t[x] < T) a[x] = 0;
			cout << X + a[x] << '\n';
		}
	}
}	

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}

