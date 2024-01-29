#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;

void solve() {
	
	int n;

	cin >> n;

	priority_queue<i64> pq;
	int ans = 0;

	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		pq.push(-x);
	}

	while((int)pq.size() > 1) {
		i64 a = -pq.top();
		pq.pop();
		if(-pq.top() == a) pq.pop();
		else {
			++ans;
			if(-pq.top() < 2 * a) {
				cout << "-1\n";
				return;
			}
		}
		pq.push(-(a << 1));
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

