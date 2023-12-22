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
	int n, k;
	i64 ans = -INFLL;

	cin >> n >> k;

	vector<int> t(n), y(n);

	for(int i = 0; i < n; ++i) cin >> t[i] >> y[i];
	
	int n1 = count(all(t), 1); 

	if(k >= n1) {
		vector<int> Y;
		i64 s = 0;
		for(int i = 0; i < n; ++i) if(t[i] == 2) Y.pb(y[i]);
		sort(rall(Y));
		for(int i = 0; i < (int)Y.size(); ++i) {
			if(n1 + (int)Y.size() - i <= k) ans = max(ans, s);
			s += Y[i];
		}
		ans = max(ans, s);
	}

	i64 s = 0;
	priority_queue<int> B;
	priority_queue<int, vector<int>, greater<int>> A;

	n1 = 0;

	for(int i = n - 1; i >= 0; --i) {
		if(t[i] == 1) {
			int r = k - n1;
		
			if(r >= 0) {

				while(!B.empty() && (int)B.size() > r) {
					s += B.top();
					A.push(B.top());
					B.pop();					
				}

				while(!A.empty() && (int)B.size() < r && A.top() < 0) {
					s -= A.top();
					B.push(A.top());
					A.pop();
				}

				while(!A.empty() && !B.empty() && A.top() < B.top()) {
					int x = A.top(); A.pop();
					int y = B.top(); B.pop();
					s += y - x;
					A.push(y);
					B.push(x);
				}
			
				ans = max(ans, y[i] + s);
			}

			++n1;
		} else {
			s += y[i];
			A.push(y[i]);
		}
	}	

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
