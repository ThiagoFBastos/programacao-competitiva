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
 
int query(int p) {
	int ans;
	cout << "? " << p << endl;
	cin >> ans;
	return ans;
}
 
void answer(int p) {
	cout << "= " << p << endl;
	exit(0);
}
 
void solve() {
	int n;
 
	cin >> n;
 
	int l = 1, r = n + 1;
 
	while(l < r) {
		int m = (l + r) / 2;
		int ans = query(m);
		if(ans > 0) r = m;
		else if(ans < 0) l = m + 1;
		else answer(m);
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	//cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
