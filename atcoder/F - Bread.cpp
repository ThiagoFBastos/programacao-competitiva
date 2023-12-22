#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	

	int n;
	i64 l, ans = 0;
	priority_queue<i64> pq;
	
	cin >> n >> l;

	for(int i = 0; i < n; ++i) {
		i64 x;
		cin >> x;
		pq.push(-x);
		l -= x;
	}

	if(l > 0) pq.push(-l);

	while((int)pq.size() > 1) {
		i64 a = -pq.top(); pq.pop();
		i64 b = -pq.top(); pq.pop();
		ans += a + b;
		pq.push(-a - b);
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

