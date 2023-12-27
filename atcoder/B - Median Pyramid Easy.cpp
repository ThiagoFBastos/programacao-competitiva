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
	
	int n, x;

	cin >> n >> x;

	if(x == 1 || x == 2 * n - 1) {
		cout << "No\n";
		return;
	}

	cout << "Yes\n";

	if(n == 2) {
		cout << "1\n2\n3\n";
		return;
	}

	vector<bool> use(2 * n + 1, true);

	if(x < 2 * n - 2) {
		use[x + 2] = use[1] = use[x] = use[x + 1] = false;
		int mid = n - 1, lo = 1;
		for(int i = 0; i < mid - 2; ++i) {
			while(!use[lo]) ++lo;
			cout << lo++ << '\n';
		}
		cout << x + 2 << '\n' << 1 << '\n' << x << '\n' << x + 1 << '\n';
		for(int i = 0; i < mid - 1; ++i) {
			while(!use[lo]) ++lo;
			cout << lo++ << '\n';
		}
		cout << '\n';
	} else {
		use[x + 1] = use[1] = use[x] = use[x - 1] = false;
		int mid = n - 1, lo = 1;
		for(int i = 0; i < mid - 1; ++i) {
			while(!use[lo]) ++lo;
			cout << lo++ << '\n';
		}
		cout << 1 << '\n' << x << '\n' << x + 1 << '\n' << x - 1 << '\n';
		for(int i = 0; i < mid - 2; ++i) {
			while(!use[lo]) ++lo;
			cout << lo++ << '\n';
		}
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
