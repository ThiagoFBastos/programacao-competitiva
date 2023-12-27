#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
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
using i128 = __int128;

void solve() {
	int n, l;
	
	cin >> n >> l;
	
	vector<int> a(n);

	for(int& v : a) cin >> v;

	int i = -1;

	for(int k = 0; k < n - 1; ++k) {
		if(a[k] + a[k + 1] >= l)
			i = k;
	}

	if(i < 0) {
		cout << "Impossible\n";
		return;
	}

	cout << "Possible\n";
	for(int k = 0; k < i; ++k) cout << k + 1 << '\n';
	for(int k = n - 2; k > i; --k) cout << k + 1 << '\n';
	cout << i + 1 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
