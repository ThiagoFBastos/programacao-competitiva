#include "bits/stdc++.h"
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int x, n;
	cin >> x >> n;
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 0; i < n; ++i) {
		int d;
		cin >> d;
		pq.push(d);
	}
	long long ans = 0;
	while(pq.size() > 1) {
		int a, b;
		a = pq.top(); pq.pop();
		b = pq.top(); pq.pop();
		ans += a + b;
		pq.push(a + b); 
	}
	cout << ans << '\n';
	return 0;
}
