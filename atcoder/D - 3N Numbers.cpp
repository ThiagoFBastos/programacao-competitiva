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
using i128 = __int128;

void solve() {
	int n;

	cin >> n;

	vector<int> a(3 * n);
	vector<i64> fh(3 * n), sh(3 * n);
	priority_queue<int> A, B;
	i64 sum = 0, best = -INFLL;

	for(int& v : a) cin >> v;

	for(int i = 0; i < 3 * n; ++i) {
		sum += a[i];
		A.push(-a[i]);
		if((int)A.size() > n) {
			sum += A.top();
			A.pop();	
		}
		fh[i] = sum;
	}

	sum = 0;

	for(int i = 3 * n - 1; i >= 0; --i) {
		sum += a[i];
		B.push(a[i]);
		if((int)B.size() > n) {
			sum -= B.top();
			B.pop();
		}
		sh[i] = sum;
	}

	for(int i = n; i <= 2 * n; ++i)
		best = max(best, fh[i - 1] - sh[i]);	

	cout << best << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

