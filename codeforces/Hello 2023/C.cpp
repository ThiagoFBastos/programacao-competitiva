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
	int n, m;

	cin >> n >> m;

	vector<i64> p(n + 1, 0), a(n + 1);
	i64 cur = 0;
	int ans = 0;
	priority_queue<i64> A;
	priority_queue<i64, vector<i64>, greater<i64>> B;

	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		p[i] = p[i - 1] + a[i];
	}

	for(int i = m + 1, lo = m + 1; i <= n; ++i) {
		p[i] += cur;
		if(p[i] < p[m]) {
			for(; lo <= i; ++lo) A.push(-2 * a[lo]);
			while(p[i] < p[m]) {
				++ans;
				cur += A.top();
				p[i] += A.top();
				A.pop(); 
			}
		}
	}

	for(int i = m - 1, lo = m; i; --i) {
		if(p[i] < p[m]) {
			for(; lo > i; --lo) B.push(-2 * a[lo]);
			while(p[m] > p[i]) {
				++ans;
				p[m] += B.top();
				B.pop();
			}	
		}
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
